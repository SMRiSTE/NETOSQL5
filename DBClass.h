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

	void re_info(int id, std::string what, std::string var) {
		pqxx::connection conn(info);
		pqxx::transaction t{ conn };
		if (what == "name" && !var.empty()) {
			t.exec_params(
				"UPDATE clients SET name = $1 WHERE id = $2;",
				var, id
			);
			t.commit();
		}
		else if (what == "last_name" && !var.empty()) {
			t.exec_params(
				"UPDATE clients SET last_name = $1 WHERE id = $2;",
				var, id
			);
			t.commit();
		}
		else if (what == "email" && !var.empty()) {
			t.exec_params(
				"UPDATE clients SET email = $1 WHERE id = $2;",
				var, id
			);
			t.commit();
		}
	}

	void del_phone(int client_id) {
		pqxx::connection conn(info);
		pqxx::transaction t{ conn };
		t.exec_params(
			"DELETE FROM numphone WHERE client_id = $1;",
			client_id
		);
		t.commit();
	}

	void del_client(int id) {
		pqxx::connection conn(info);
		pqxx::transaction t{ conn };
		t.exec_params(
			"DELETE FROM clients WHERE id = $1;",
			id
		);
		t.commit();
	}

	void find(std::string what, std::string var) {
		pqxx::connection conn(info);
		pqxx::transaction t{ conn };

		if (what == "name" && !var.empty()) {
			t.exec_params(
				"SELECT * FROM clients WHERE name = $1;",
				var
			);
			t.commit();

			std::cout << "DONE" << std::endl;
		}
		else if (what == "last_name" && !var.empty()) {
			t.exec_params(
				"SELECT * FROM clients WHERE last_name = $1;",
				var
			);
			t.commit();

			std::cout << "DONE" << std::endl;
		}
		else if (what == "email" && !var.empty()) {
			t.exec_params(
				"SELECT * FROM clients WHERE email = $1;",
				var
			);
			t.commit();

			std::cout << "DONE" << std::endl;
		}
		else if (what == "num_phone" && !var.empty()) {
			
			t.exec_params(
				"SELECT * FROM clients c LEFT JOIN numphone n ON n.client_id = c.id WHERE n.numphone = $1;",
				var
			);
			t.commit();

			std::cout << "DONE" << std::endl;
		}
	}
};