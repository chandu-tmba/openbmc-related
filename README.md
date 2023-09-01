# openbmc-related
files related to openbmc


| D-Bus Data Type | Value of the D-Bus Property in case of Error | Property Value as seen on Redfish |
|-----------------|---------------------------------------------|----------------------------------|
| INT16           | INT_MAX                                     | null                             |
| UINT16          | UINT_MAX                                    | null                             |
| INT32           | LONG_MAX                                    | null                             |
| UINT32          | ULONG_MAX                                   | null                             |
| INT64           | LLONG_MAX                                   | null                             |
| UINT64          | ULLONG_MAX                                  | null                             |
| DOUBLE          | std::numeric_limits<T>::quiet_NaN()        | null                             |
| STRING          | BE_ERROR-XXX                                | null                             |
| BOOL            | uint8_t {0–false, 1–true, others- error}    | null                             |
