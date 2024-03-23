#include <iostream>
#include <mysql/mysql.h>

using namespace std;

class Telephone {
private:
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int qstate;

public:
    Telephone() {
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "192.168.1.4", "", "0000", "cpp_telephone_management", 0, NULL, 0);
        if (!conn) {
            cout << "Error while connecting to database: " << mysql_error(conn) << "\n";
        } else {
            cout << "Successfully connected to database" << "\n";
        }
    }

    void addBill() {
        viewCustomerNamesAndId();
        int id = getId();
        bool idExists = checkIDinCustomers(id);

        if (idExists) {
            if (isNotBilled(id)) {
                float call, sms, mms, total;
                cout << "Enter total call, total sms, and total mms: ";
                cin >> call >> sms >> mms;

                total = call + sms + mms;

                insertBill(call, sms, mms, total, id);
            } else {
                cout << "Customer is already billed" << "\n";
            }
        } else {
            cout << "Customer does not exist" << "\n";
        }
    }

    void viewCustomerNamesAndId() {
        qstate = mysql_query(conn, "SELECT customer_id,name FROM customers");
        if (!qstate) {
            res = mysql_store_result(conn);
            cout << "ID   Name" << "\n";
            cout << "\n";
            while ((row = mysql_fetch_row(res))) {
                cout << row[0] << " | " << row[1] << "\n";
            }
        } else {
            cout << "Query error: " << mysql_error(conn) << "\n";
        }
        mysql_free_result(res);
    }

    int getId() {
        int id;
        cout << "Select user ID: ";
        cin >> id;
        return id;
    }

    bool checkIDinCustomers(int id) {
        stringstream s;
        s << id;
        string strID;
        s >> strID;
        string query = "SELECT customer_id FROM customers WHERE customer_id = " + strID;
        int qstate = mysql_query(conn, query.c_str());

        if (qstate != 0) {
            cout << "Error executing query" << "\n";
            return false;
        } else {
            res = mysql_store_result(conn);

            if (!res) return false;

            bool idExists = (mysql_num_rows(res) > 0);
            mysql_free_result(res);

            return idExists;
        }
    }

    bool isNotBilled(int id) {
        stringstream s;
        s << id;
        string strID;
        s >> strID;
        string query = "SELECT customer_id FROM bills WHERE customer_id = " + strID;
        int qstate = mysql_query(conn, query.c_str());

        if (qstate != 0) {
            cout << "Error executing query" << "\n";
            return false;
        } else {
            res = mysql_store_result(conn);

            if (!res) return false;

            bool idNotExists = (mysql_num_rows(res) == 0);
            mysql_free_result(res);

            return idNotExists;
        }
    }

    void insertBill(float call, float sms, float mms, float total, int id) {
        string query = "INSERT INTO bills(customer_id,calls,mms,sms,total_bill) VALUES('" + to_string(id) + "','" + to_string(call) +
                       "','" + to_string(mms) + "','" + to_string(sms) + "','" + to_string(total) + "')";
        cout << query << "\n";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

        if (qstate == 0) {
            cout << "Record inserted" << "\n";
        } else {
            cout << "Cannot insert record" << "\n";
        }
    }

    void addCustomer() {
        cout << "Enter customer name, address, street, pin, phone, and account: ";
        string name, address, street, account;
        int phone;
        bool pin;

        cin >> name >> address >> street >> pin >> phone >> account;

        string query = "INSERT INTO customers(name,address,street,pin,phone,account) VALUES('" + name + "','" + address +
                       "','" + street + "','" + to_string(pin) + "','" + to_string(phone) + "','" + account + "')";
        cout << query;
    }
};

int main() {
    Telephone telephone;
    return 0;
}
