// github.com/A3st76/mysql_crypto. Source file under MIT license.

#pragma once

#include "database_handler.h"
#include "data_miner.h"

extern std::unique_ptr<DatabaseHandler> g_database_handler;
extern std::unique_ptr<DataMiner> g_data_miner;