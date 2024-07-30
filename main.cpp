#include<iostream>
#include <pqxx/pqxx>
#include "DBClass.h"
#include <Windows.h>
#pragma execution_character_set( "utf-8" )

int main() {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	try {
		DB DB("host=localhost port=5432 dbname=HW5 user=postgres password=HORPUYER");
		DB.CreateTable();
		/*DB.add_client("Boy", "Shev", "s.m.r.00800ist");*/
		DB.add_phone(1, "1234567890");
		DB.re_info(1, "num_phone", "0987654321");
		DB.find("num_phone", "0987654321");
	}
	catch(pqxx::sql_error e){
		std::cout << e.what() << std::endl;
	}
}