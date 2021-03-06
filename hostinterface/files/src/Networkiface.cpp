/*
// Copyright (c) 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#include <unistd.h>

#include <Networkiface.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <sdbusplus/asio/connection.hpp>
#include <sdbusplus/asio/object_server.hpp>
#include <string>


using namespace std;

Networkiface::Networkiface(const std::string& name , const std::string& id , const std::string& state , const std::string& health ,
		     sdbusplus::asio::object_server& objectServer,
                     std::shared_ptr<sdbusplus::asio::connection>& conn,
                     boost::asio::io_service& io) : 
	objServer(objectServer) ,name(name)
{
	(void)conn;
	(void)io;
	networkInterface = objectServer.add_interface(
			"/xyz/openbmc_project/HostInventory/NetworkIfaces/" + name,
			"xyz.openbmc_project.HostInventory.Item.NetworkIface");

	association = objectServer.add_interface(
			"/xyz/openbmc_project/HostInventory/NetworkIfaces/" + name,
			"org.openbmc.Associations");

	statusInterface = objectServer.add_interface(
                        "/xyz/openbmc_project/HostInventory/NetworkIfaces/" + name,
                        "xyz.openbmc_project.HostInventory.Item.Status");


	//setting proeproties of interface
	networkInterface->register_property("Name", name);
	networkInterface->register_property("Id", id);

	if (!networkInterface->initialize())
	{

		std::cerr << "error initializing eth interface\n";
	}

        statusInterface->register_property("State", state);
        statusInterface->register_property("Health", health);

        if (!statusInterface->initialize())
        {

                std::cerr << "error initializing status interface\n";
        }



}

Networkiface::~Networkiface()
{

	objServer.remove_interface(networkInterface);
	objServer.remove_interface(association);
}


