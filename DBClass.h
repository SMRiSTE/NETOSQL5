#pragma once
#include<string>
#include<pqxx/pqxx>
class DB {
private:
	std::string info;

public:
	DB(std::string conn) {
		this->info = conn;
	}

	void CreateTable() {
		pqxx::connection conn(info);
		pqxx::work t{ conn };

		t.exec(
			"CREATE TABLE IF NOT EXISTS clients ( "
			"id SERIAL PRIMARY KEY, "
			"name VARCHAR(100) NOT NULL, "
			"last_name VARCHAR(100) NOT NULL, "
			"email VARCHAR(100) NOT NULL UNIQUE "
			");"
		);

		t.exec(
			"CREATE TABLE IF NOT EXISTS numphone ( "
			"id SERIAL PRIMARY KEY, "
			"client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE, "
			"numphone VARCHAR(100) "
			");"
		);

		t.commit();
	}


	void add_client(std::string name, std::string last_name, std::string email) {
		pqxx::connection conn(info);
		pqxx::transaction t{ conn };
		t.exec_params(
			"INSERT INTO clients(name, last_name, email) VALUES($1, $2, $3)",
			name, last_name, email
		);
		t.commit();
	}

	void add_phone(int client_id, std::string numphone) {
		pqxx::connection conn(info);
		pqxx::transaction t{ conn };
		t.exec_params(
			"INSERT INTO numphone(client_id, numphone) VALUES($1, $2)",
			client_id, numphone
		);
		t.commit();
	}
};