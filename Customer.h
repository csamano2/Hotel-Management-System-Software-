/*
Purpose: Customer Class for Hotel System 
-- This class will include account information, reservation, and reward system all for the customer 
*/


#include <iostream>
#include <string>
#include <vector>
#include "Reservartions.h"

using namespace std;

class userCustomer{
private:
	int cUsernameSize;
	int cPasswordSize;
	// Customer Account Datatypes 
	//int customerID = 0;
	//int rewards = 0;
	string firstName = " ";
	string lastName = " "; 
	string userName = " ";
	string phoneNumber = " ";
	string emailAddress = " ";
	string password = " ";

	//Customer Reservation Datatypes 
	//string customerFirstName, customerLastName, duration;
	//string month, day, year, monthOut, dayOut, yearOut;
	int package, guest;
	string  y = "yes";
	string n = "no";
	string customerCheckIn = " / / /", customerCheckOut = " / / /";
	HotelDB  hotel; 
	reservationClass res;
	MenuHelper mh;
	//map <string, string> cInfo;

		// Customer Interface Screen 
	void customerMenuOptionOne()
	{
		int num = 0;
		string menuOptions[] = { "Create Account", "Login to System" };
		mh.printMenu("Welcome to Mo's Hotel System", 2, menuOptions, " Please make a choice:");

		/*cout << "**************************************" << endl;
		cout << "    Welcome to Mo's Hotel System      " << endl;
		cout << "**************************************" << endl;
		cout << "     1. Create Account" << endl;
		cout << "     2. Login to System" << endl;
		cout << " Please make a choice:" << endl;
		cin >> num;*/

		//for (int i = 0; i < num; i++) {
		switch (mh.SelectedItem) {
		case 1:
			customerCreateAccount();
			break;
		case 2:
			customerLogin();
			break;
		default:
			break;
		}
		//}
	}

public: 
	bool customerDataLoaded = false;
	bool customerSaved = false;
	int customerID = 0;
	int currentRewards = 0;

#pragma region Database Calls

	void getCustomerData(string u, string p)
	{
		string query = "CALL GetCustomerData('" + u + "', '" + p + "')";
		map <string, string> cInfo = hotel.getCustomerData(query);

		// Set the data
		if (!cInfo.empty()) {
			customerID = stoi(cInfo["CustomerID"]);
			currentRewards = stoi(cInfo["RewardsPoints"]);
			firstName = cInfo["FirstName"];
			lastName = cInfo["LastName"];
			userName = cInfo["UserName"];
			password = cInfo["Password"];
			phoneNumber = cInfo["PhoneNumber"];
			emailAddress = cInfo["EmailAddress"];
			currentRewards = stoi(cInfo["RewardsPoints"]);
			customerDataLoaded = true;
			cInfo.clear();
		}
		else
		{
			customerDataLoaded = false;
		}
	}

	void saveCustomerData(string cUserName, string cPassword, string cFirstName, string cLastName, string cEmailAddress, string cPhoneNumber)
	{
		string query = "CALL SaveCustomerData('" + cFirstName + "', '" + cLastName + "', '" + cUserName + "', '" + cPassword + "', '" + cPhoneNumber + "', '" + cEmailAddress + "')";
		customerSaved = hotel.saveToDatabase(query);
	}

#pragma endregion

/* CUSTOMER ACCOUNT */


	// Customer Menu Option for Login
	void customerMenuOptionTwo() {
		int customerChoice;
		cout << endl;
		cout << "******************************************" << endl;
		cout << "        MO's Hotel Customer Account " << endl;
		cout << "******************************************" << endl;
		cout << "       1. Account Information" << endl;
		cout << "       2. Reservation" << endl;
		cout << "       3. Reward Points " << endl;
		cout << "       4. Hotel Amentities" << endl;
		cout << "	    Press 'X' to exit! " << endl;
		cout << "       Please Make a Choice: ";
		cin >> customerChoice;
		switch (customerChoice) {
		case 1:
			customerAccountInformation();
			break;
		case 2:
			customerReservation();
			break;
		case 3:
			customerRewardPoints();
			break;
		case 4:
			customerHotelAmentities();
			break;
		default:
			cout << endl;
			cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
			cout << "GOODBYE :)" << endl;
			break;
		}
	}

	//bool checkLength(string text, int maxLength)
	//{
	//	if (text.length() > maxLength || text.length() < maxLength)
	//	{
	//		return false;
	//	}
	//	return true;
	//}

// Customer Account Information Function
	void customerCreateAccount() 
	{
		string userName, password, firstName, lastName, emailAddress, phoneNumber = "";
		//Customer Enters Account Information 
		cout << "To create your account, please enter the following details below: " << endl;
		cout << "Name: ";
		cin >> firstName >> lastName;
		cout << "Email: ";
		cin >> emailAddress;
		cout << "Phone Number: ";
		cin >> phoneNumber;
		cout << "Username (Must be at least 8 characters) : ";
		cin >> userName;
		cout << endl;

		// Checking the size of the username 
		while (!mh.checkLength(userName, 8))
		{
			cout << "Remember your username has to be 8 characters long. Please try again!" << endl;
			cout << "Username: ";
			cin >> userName;
		}

		cout << "Password (Must be at least 6 characters): ";
		cin >> password;
		cout << endl;

		// Checking the size of the password 
		while (!mh.checkLength(password, 6))
		{
			cout << "Remember your password has to be 6 characters long. Please try again!" << endl;
			cout << "Password: ";
			cin >> password;
		}

		// Save Customer Account Info 
		saveCustomerData(userName, password, firstName, lastName, emailAddress, phoneNumber);
		
		if (customerSaved)
		{
			cout << "You're Account Information has been saved! " << endl;
			cout << "To Proceed, Please Login! " << endl;
		}
		else
		{
			cout << "Account information could not be saved! Please try again! " << endl;
			customerMenuOptionTwo();
		}

		customerLogin();
	}

// Customer Login to System 
	void customerLogin() {
		string line;
		string userName, password = "";
		cout << endl;
		cout << " Welcome to Mo's Hotel " << endl;
		cout << "Username: " << endl;
		cin >> userName;
		cout << endl;

		// Checking the size of the username 
		while (!mh.checkLength(userName, 8))
		{
			cout << "Remember your username has to be 8 characters long. Please try again!" << endl;
			cin >> userName;
		}

		cout << "Password: " << endl;
		cin >> password;
		cout << endl;

		// Checking the size of the password 
		while (!mh.checkLength(password, 6))
		{
			cout << "Remember your password has to be 6 characters long. Please try again!" << endl;
			cin >> password;
		}

		// Get Customer data
		getCustomerData(userName, password);

		if (customerDataLoaded) 
		{
			customerMenuOptionTwo();
		}
		else
		{
			cout << "Unable to retrieve account information. Please try again!" << endl;
			customerLogin();
		}
		
	}
// Customer Account File Information

	void customerAccountInformation() {
		string y = "yes";
		cout << endl << "     Customer Account Details" << endl;
		cout << " Name: " << firstName <<" "<< lastName << endl;
		cout << " Email: " << emailAddress << endl;
		cout << " Phone Number: " << phoneNumber << endl;
		cout << " Username: " << userName << endl;
		cout << " Password: " << password << endl;

		cout << "Would you like to go back to the home screen? ";
		if (cin >> y) {
			customerMenuOptionTwo();
		}
		else {
			cout << "Thank you for choicing Mo's Hotel we look forward to serving you in the future! " << endl;
		}
	}

/* RESERVATIONS FOR CUSTOMER*/

// Customer Reservation Menu Fucntion 
	void customerReservation() {
		string y = "yes";
		string n = "no";
		int choice;
		cout << endl;
		cout << "******** Reservations ********" << endl;
		cout << "1. Book New Reservation " << endl;
		cout << "2. Cancel Current Reservation " << endl;
		cout << "Please Make a Choice: ";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 1:
			customerBookReservations();
		case 2:
			cancelCustomerReservation();
			break;
		default:
			break;
		}
	}
// Customer Reservations Bookings 
	void customerBookReservations() {
		string m, d, y = "";
		string m1, d1, y1 = "";
		string customerFirstName, customerLastName = "";

		cout << "To begin a new reservations booking, please enter the following details below: " << endl;
		cout << "First Name: ";
		cin >> customerFirstName;
		cout << "Last Name: ";
		cin >> customerLastName;
		cout << "# of Guest: ";
		cin >> guest; 
		customerCheckIn = res.checkInDate(m, d, y);
		customerCheckOut = res.checkOutDate(m1, d1, y1);

		cout << "Packages: ";//, Would you like a special type? ";
//		if (cin >> y) {
			cout << endl;
			customerRoomPackages(); // NOTE: Add fields if they are avaiable or not
	//	}
		
	}

	// Customer Room Packages Function
	void customerRoomPackages() {
		string y = "yes";
		string n = "no";
		int amentityOption = 0;
		int daysForAmen = 0;
		int total = 0;
		int adjustedRewards = currentRewards;

		vector<map<string, string>> allPackageInfo = hotel.getPackageTypes();
		map<string, string> selectedPackage;
		map<string, string> selectedAddon;
		vector<map<string, string>> allAddonInfo;
		// Room Packages Information 
		cout << endl;
		cout << "The Following Room Packages are listed below: " << endl;
		cout << endl;

		for (int i = 0; i < allPackageInfo.size(); i++)
		{
			cout << i + 1 << ". " << allPackageInfo[i]["PackageName"] << endl;
			cout << "Includes " << allPackageInfo[i]["PackageDescription"] << endl;
			if (allPackageInfo[i]["Amentities"] != "") {
				cout << "Hotel Amentities Included: " << allPackageInfo[i]["Amentities"] << endl;
			}
			cout << "Price: $" << allPackageInfo[i]["BaseCost"] << " a night" << endl << endl;
		}

		cout << "Which Package Would you like? ";
		package = mh.menuOptionCheck(package, allPackageInfo.size(), "Please select from the packages listed above.");

		if (package != 0) {
			selectedPackage = allPackageInfo[package - 1];
			cout << "You've selected the " << selectedPackage["PackageName"] << ", excellent choice! " << endl;
			cout << endl;
		}

		cout << "Would you like you to add on any amentities? " << endl << endl;

		if (cin >> y) {
			cout << "**** Hotel Amentities Add Ons ****" << endl;
			allAddonInfo = hotel.getAddons();

			// Display all available addons
			for (int i = 0; i < allAddonInfo.size(); i++)
			{
				cout << i + 1 << ". " << allAddonInfo[i]["AmenityName"] << " $" << allAddonInfo[i]["BaseCost"] << " a day," << allAddonInfo[i]["AmenityDescription"] << endl;
			}

			cout << "Which amentities would you like to add? " << endl;
			amentityOption = mh.menuOptionCheck(amentityOption, allAddonInfo.size(), "Please select from the amentities listed above.");

			if (amentityOption != 0) {
				selectedAddon = allAddonInfo[amentityOption - 1];

				cout << endl;
				cout << "**** " << selectedAddon["AmenityName"] << " *****" << endl;
				cout << "How many days would you like to use the " << selectedAddon["AmenityName"] << " during your stay? ";
				cin >> daysForAmen;
				cout << "$" << stoi(selectedAddon["BaseCost"]) * daysForAmen << " added to your bill" << endl;
			}

			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			cout << endl;

			total = stoi(selectedPackage["BaseCost"]) + (stoi(selectedAddon["BaseCost"]) * daysForAmen);
			cout << "Payment Total: $" << total << endl;
			res.getPayment();
			cout << endl;

			// Calculate Rewards
			adjustedRewards += total;
			
			// Save reservation
			res.saveReservation(customerID, guest, customerCheckIn, customerCheckOut, selectedPackage["PackageTypeID"], selectedAddon["AddOnID"], daysForAmen, total, adjustedRewards, 0, 0);

			if (res.reservationSaved)
			{
				cout << "Your Reservation has been saved!" << endl;
			}

			cout << "Would you like to go back to home menu? ";
			if (cin >> y) {
				customerMenuOptionTwo();
			}
			else if (cin >> n) {
				cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
			}
		}
		else if (cin >> n) {
			
			// Calculate Rewards
			adjustedRewards += total; // NOTE Need to get the toatl cost

			// Save reservation
			res.saveReservation(customerID, guest, customerCheckIn, customerCheckOut, selectedPackage["PackageTypeID"], selectedAddon["AddOnID"], daysForAmen, total, adjustedRewards, 0, 0);

			cout << "Click Next to proceed with payments: " << " NEXT..... " << endl;
			cout << endl;
			res.getPayment();
			cout << endl;
			cout << "Would you like to go back to home menu? ";
			if (cin >> y) {
				customerMenuOptionTwo();
			}
			else if (cin >> n) {
				cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
			}
		}
	}


	// Cancel Booking Reservations
	void cancelCustomerReservation() 
	{
		res.cancelCustomerReservation(customerID);

		if (res.reservationCancelled)
		{
			cout << "Your reservation has been cancelled. If you would like to create a new reservation, please go back to the home screen! " << endl;
			customerMenuOptionTwo();
		}
		else
		{
			// Has a reservation but did not want to cancell it
			if (res.foundRes) 
			{
				cout << "Your reservation was NOT cancelled." << endl;
			}

			customerMenuOptionTwo();
		}
	}

	// Customer Looks at reward points 
	void customerRewardPoints() {

		int selectedMenuItem = 0;
		vector<map<string, string>> eligibleRewards;
		map<string, string> selectedReward;
		int requiredRewards, adjustedRewards, reward = 0;
		string query = "";

		if (!customerDataLoaded)
		{
			cout << "Unable to retrieve Rewards. Please try again later..." << endl;
			customerMenuOptionTwo();
		}

		// Display customer name and rewards
		cout << endl << endl << "            Customer Rewards Details      " << endl;
		cout << "Name: " << firstName<< " " <<lastName << endl;
		cout << "Current Rewards Total: " << currentRewards << endl << endl;

		cout << "Please select an option below or select '0' to return to the main menu:" << endl;
		cout << " 1. Redeem Rewards" << endl;
		/*cout << " 2. View Rewards History" << endl;*/
		cout << " 2. How Rewards Work" << endl;

		selectedMenuItem = mh.menuOptionCheck(selectedMenuItem, 3, "Please select an option below or select '0' to return to the main menu:");

		switch (selectedMenuItem)
		{
		case 1:
			// Redeem Rewards

			// Get Eligible Rewards
			eligibleRewards = hotel.getEligibleRewards(customerID);

			if (eligibleRewards.size() == 0) {
				cout << "Whoops! Looks like you are not eliglble for rewards at this time. Please make a reservation to gather more points!" << endl << endl;
				customerMenuOptionTwo();
			}

			// Display Eligible Rewards
			cout << "Please Select the reward you would like to redeem." << endl << endl;
			for (int i = 0; i < eligibleRewards.size(); i++)
			{
				cout << i + 1 << ". Reward : " << eligibleRewards[i]["RewardName"] << endl;
				cout << "   Details : " << eligibleRewards[i]["RewardDescription"] << endl;
				cout << "   Cost : " << eligibleRewards[i]["RequiredRewards"] << "pts" << endl << endl;
			}

			reward = mh.menuOptionCheck(reward, eligibleRewards.size(), "Please Select the reward you would like to redeem.");
			
			if (reward != 0) 
			{
				// Get the selected Reward
				selectedReward = eligibleRewards[reward - 1];

				// Adjust Rewards Points
				requiredRewards = stoi(selectedReward["RequiredRewards"]);
				adjustedRewards = currentRewards - requiredRewards;

				// Update customers total rewards
				query = "CALL UpdateRewards(" + to_string(customerID) + "," + to_string(adjustedRewards) + ")";
				hotel.saveToDatabase(query);

				// Apply reward to Reservation and adjust pricing(if any)
				//cout << "Reward Points amount = 195 " << endl;
				//cout << "It'll be added to your account! " << endl;

				// Add Rewards Transaction to the Rewards log
			}

			customerMenuOptionTwo();
		//case 2:
		//	// View Rewards History (would have to create separate table to house all the rewards transactions)
		//	customerMenuOptionTwo();
		case 2:
			// How Rewards Work
			cout << "The Reward Points are based on the price of the room. They price of a reservation will be the amount of points a customer is awarded when they make a reservation." << endl;
			cout << "Points are awarded each time a customer schedules a reservation." << endl << endl;
			customerMenuOptionTwo();
		default:
			customerMenuOptionTwo();
		}
	}

	// Customer see hotel amentities
	void customerHotelAmentities() {
		int selectedChoice = 0;
		string y = "yes";
		string n = "no";

		// Get all reservations for a customer and display them
		vector<map<string, string>> allAmenities = hotel.getHotelAmenities();
		map<string, string> selectedAmenity;

		cout << endl << "***** Mo's Hotels Amentities *****" << endl;
		cout << "With your stay you have the option to enjoy the following amentities below: " << endl;

		for (int i = 0; i < allAmenities.size(); i++)
		{
			cout << i + 1 << ". " << allAmenities[i]["AmenityName"] << endl;
		}
		
		selectedChoice = mh.menuOptionCheck(selectedChoice, allAmenities.size(), " If you want more information on each option, please select an option above ");
		
		if (selectedChoice != 0) {
			selectedAmenity = allAmenities[selectedChoice - 1];

			cout << endl << "******** " << selectedAmenity["AmenityName"] << " ********" << endl;
			cout << selectedAmenity["AmenityDescription"] << endl;
			cout << selectedAmenity["Auxiliary1"] << endl;
			cout << selectedAmenity["Auxiliary2"] << endl;
			cout << selectedAmenity["Auxiliary3"] << endl;
			cout << selectedAmenity["Auxiliary4"] << endl;
			cout << selectedAmenity["Auxiliary5"] << endl;

			cout << "Thank you!!!!" << endl;
			cout << endl;
			cout << "Would you like to go back to home menu? ";
			if (cin >> y) {
				customerMenuOptionTwo();
			}
			else if (cin >> n) {
				cout << "Thank you for choicing MO's Hotels, We look forward to serving you in the future! " << endl;
			}
		}
		else 
		{
			customerMenuOptionTwo();
		}
	}
};
