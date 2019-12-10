#include <iostream>
#include <string>
#include <mysql.h>	// Database connection
#include <map>	   
#include <vector>
#include "ConnectionProperties.h" // Database connection string
using namespace std;

class HotelDB
{
private:
	MYSQL* conn;
	
public:
	map <string, string> getCustomerData(string query)
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			map <string, string> cInfo;
			int qstate;

			startConnection();

			if (conn)
			{
				throw exception("Connection error.");
			}

			// Call the stored procedure from the database
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				throw exception("Query error.");
			}

			res = mysql_store_result(conn);

			int num_Fields = mysql_num_fields(res);
			fields = mysql_fetch_fields(res);

			while (row = mysql_fetch_row(res))
			{
				// Create a dictionary to house the data we will retrieve from the database
				cInfo = {
					{"CustomerID"   , ""},
					{"FirstName"	, ""},
					{"LastName"		, ""},
					{"UserName"	    , ""},
					{"Password"	    , ""},
					{"PhoneNumber"  , ""},
					{"EmailAddress" , ""},
					{"RewardsPoints", ""}
				};

				for (int i = 0; i < num_Fields; i++)
				{
					if (row[i] != nullptr)
					{
						cInfo[fields[i].name] = row[i];
					}
				}
			}

			return cInfo;
		}
		catch (exception e)
		{
			throw exception("Error connecting to database.");
		}
	}
	
	map <string, string> getEmployeeData(string query)
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			map <string, string> eInfo;
			int qstate;

			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);

					int numOfFields = mysql_num_fields(res);
					fields = mysql_fetch_fields(res);

					while (row = mysql_fetch_row(res))
					{
						// Create a dictionary to house the data we will retrieve from the database
						eInfo = {
							{"EmployeeID"   , ""},
							{"FirstName"	, ""},
							{"LastName"		, ""},
							{"UserID"	    , ""},
							{"Password"	    , ""},
						};

						for (int i = 0; i < numOfFields; i++)
						{
							eInfo[fields[i].name] = row[i];
						
						}
					}
				}
			}

			return eInfo;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getReservations(int customerID)
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the reservations
			vector<map<string, string>> allCustomerReservations;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> rInfo = {
				{"ReservationID"	 , ""},
				{"PackageID"		 , ""},
				{"PackageTypeID"	 , ""},
				{"PackageName"		 , ""},
				{"BaseCost"			 , ""},
				{"AmenityName"		 , ""},
				{"AddOnDays"		 , ""},
				{"TotalCost"		 , ""},
				{"FirstName"		 , ""},
				{"LastName"			 , ""},
				{"NumberOfGuests"	 , ""},
				{"CheckInDate"	     , ""},
				{"CheckOutDate"	     , ""},
			};

			// Connect to Database
			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetReservations(" + to_string(customerID) + ")";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);

					int numOfFields = mysql_num_fields(res);
					fields = mysql_fetch_fields(res);

					while (row = mysql_fetch_row(res))
					{
						for (int i = 0; i < numOfFields; i++)
						{
							if (row[i] != nullptr)
								rInfo[fields[i].name] = row[i];
						}

						allCustomerReservations.push_back(rInfo);
						rInfo.clear();
					}					
				}
				else
				{
					cout << "Unable to retrieve your reservations." << endl;
				}
			}

			return allCustomerReservations;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getPackageTypes()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the package types
			vector<map<string, string>> allPackageTypes;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> ptInfo = {
				{"PackageTypeID"	,		""},
				{"PackageName"	,			""},
				{"PackageDescription",		""},
				{"Amentities",				""},
				{"BaseCost",				""},
				{"Available",				""},
				{"UnderMaintenance",		""}
			};

			// Connect to Database
			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetPackageTypes()";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);

					int numOfFields = mysql_num_fields(res);
					fields = mysql_fetch_fields(res);

					while (row = mysql_fetch_row(res))
					{
						for (int i = 0; i < numOfFields; i++)
						{
							if(row[i] != nullptr)
								ptInfo[fields[i].name] = row[i];
						}
						
						allPackageTypes.push_back(ptInfo);
						ptInfo.clear();
					}
				}
				else
				{
					cout << "Packages unavailable." << endl;
				}
			}

			return allPackageTypes;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getAddons()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the addons
			vector<map<string, string>> allAddons;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> addInfo = {
				{ "AddOnID"	,			"" },
			{ "AmenityName"	,			"" },
			{ "AmenityDescription",		"" },
			{ "BaseCost",				"" }
			};

			// Connect to Database
			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetAddons()";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);

					int numOfFields = mysql_num_fields(res);
					fields = mysql_fetch_fields(res);

					while (row = mysql_fetch_row(res))
					{
						for (int i = 0; i < numOfFields; i++)
						{
							if (row[i] != nullptr)
								addInfo[fields[i].name] = row[i];
						}

						allAddons.push_back(addInfo);
						addInfo.clear();
					}

				}
				else
				{
					cout << "Amentities unavailable." << endl;
				}
			}

			return allAddons;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getHotelAmenities()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the addons
			vector<map<string, string>> allAmenities;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> aInfo = {
				{"AmenityName"	,			""},
				{"AmenityDescription",		""},
				{"Auxiliary1"	,			""},
				{"Auxiliary2"	,			""},
				{"Auxiliary3"	,			""},
				{"Auxiliary4"	,			""},
				{"Auxiliary5"	,			""},
			};

			// Connect to Database
			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetHotelAmenities()";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);

					int numOfFields = mysql_num_fields(res);
					fields = mysql_fetch_fields(res);

					while (row = mysql_fetch_row(res))
					{
						for (int i = 0; i < numOfFields; i++)
						{
							if (row[i] != nullptr)
								aInfo[fields[i].name] = row[i];
						}

						allAmenities.push_back(aInfo);
						aInfo.clear();
					}

				}
				else
				{
					cout << "Amentities unavailable." << endl;
				}
			}

			return allAmenities;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}
	
	vector<map<string, string>> getEligibleRewards(int customerID)
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the Rewards Rewards
			vector<map<string, string>> allRewards;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> rInfo = {
				{"RewardID",			""},
				{"RewardName",			""},
				{"RewardDescription",	""},
				{"RequiredRewards",		""}
			};

			// Connect to Database
			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL GetEligibleRewards(" + to_string(customerID) + ")";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);

					int numOfFields = mysql_num_fields(res);
					fields = mysql_fetch_fields(res);

					while (row = mysql_fetch_row(res))
					{
						for (int i = 0; i < numOfFields; i++)
						{
							if (row[i] != nullptr)
								rInfo[fields[i].name] = row[i];
						}

						allRewards.push_back(rInfo);
						rInfo.clear();
					}

				}
				else
				{
					cout << "Rewards unavailable." << endl;
				}
			}

			return allRewards;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	vector<map<string, string>> getSummaryReport()
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			MYSQL_FIELD *fields;
			int qstate;

			// Create a vector that will hold all the package types
			vector<map<string, string>> summaryReport;

			// Create a dictionary to house the data we will retrieve from the database
			map <string, string> ptInfo = {
				{"numReservations"	,		""},
				{"numRoomsAvailable"	,		""},
				{"numUnderMaintenance",		""},
			};

			// Connect to Database
			startConnection();

			if (conn)
			{
				// Call the stored procedure from the database
				string query = "CALL SummaryReport()";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);

					int numOfFields = mysql_num_fields(res);
					fields = mysql_fetch_fields(res);

					while (row = mysql_fetch_row(res))
					{
						for (int i = 0; i < numOfFields; i++)
						{
							if (row[i] != nullptr)
								ptInfo[fields[i].name] = row[i];
						}

						summaryReport.push_back(ptInfo);
						ptInfo.clear();
					}
				}
				else
				{
					cout << "Summary Report unavailable." << endl;
				}
			}

			return summaryReport;
		}
		catch (exception e)
		{
			throw exception("Error connecting to our database.");
		}
	}

	bool saveToDatabase(string query)
	{
		try
		{
			MYSQL_RES * res;
			MYSQL_ROW row;
			int qstate;

			startConnection();

			if (conn)
			{
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		catch (exception e)
		{
			throw exception("Error connecting to the database.");
		}
	}

	void startConnection() {
		try
		{
			int qstate;
			conn = mysql_init(0);
			conn = mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0);

			if (conn)
			{
				throw exception("Connection error.");
			}

			cout << endl;
			cout << "Connection to MySQL successful, connecting to HotelSystemDB..." << endl;

			// Check if the database exists
			string query = "USE HotelSystemDB;";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				throw exception("Connection to HotelSystemDB failed.");
			}

		}
		catch (exception e)
		{
			cout << "Error connecting to database" << endl;
		}
	}

};

class MenuHelper
{
private:
	//string titleTexts[];

public:
	int SelectedItem = 0;
	void createAccountPrompt() 
	{
	}

	// Interface Menus
	void printMenu(string titleText, int menuSize, string menuOptions[], string instructionText)
	{
		SelectedItem = 0;
		bool continueToNextMenu = false;
		do {
			if (titleText != "") {
				cout << "**************************************" << endl;
				cout << titleText << endl;
				cout << "**************************************" << endl;
				for (int i = 0; i < menuSize; i++)
				{
					cout << "     " << i + 1 << ". " << menuOptions[i] << " " << endl;
				}
			}

			SelectedItem = menuOptionCheck2(menuSize, instructionText);

			if (SelectedItem != 0)
			{
				continueToNextMenu = true;
			}

		} while (!continueToNextMenu);
	}

	int menuOptionCheck2( int menuSize, string message)
	{
		cout << message << endl;
		cin >> SelectedItem;

		while (SelectedItem == 0 || SelectedItem > menuSize)
		{
			if (SelectedItem == 0) {
				return 0; //NOTE
			}

			cout << message << endl;
			cin >> SelectedItem;
		}

		return SelectedItem;
	}


	int menuOptionCheck(int selectedItem, int menuSize, string message)
	{
		cout << message << endl;
		cin >> selectedItem;

		while (selectedItem == 0 || selectedItem > menuSize)
		{
			if (selectedItem == 0) {
				return 0; //NOTE
			}

			cout << message << endl;
			cin >> selectedItem;
		}

		return selectedItem;
	}

	bool checkLength(string text, int maxLength)
	{
		if (text.length() > maxLength || text.length() < maxLength)
		{
			return false;
		}
		return true;
	}

};