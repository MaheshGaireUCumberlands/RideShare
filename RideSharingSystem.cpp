#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
using namespace std;

// Base Ride class
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance; // in miles

public:
    Ride(int id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    virtual double fare() const = 0; // pure virtual
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID << "\nPickup: " << pickupLocation
             << "\nDropoff: " << dropoffLocation << "\nDistance: " << distance << " miles" << endl;
    }

    virtual ~Ride() {}
};

// StandardRide subclass
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 1.5; // $1.5 per mile
    }

    void rideDetails() const override {
        cout << "\n[Standard Ride]" << endl;
        Ride::rideDetails();
        cout << "Fare: $" << fixed << setprecision(2) << fare() << endl;
    }
};

// PremiumRide subclass
class PremiumRide : public Ride {
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 3.0 + 5.0; // $3 per mile + $5 base fee
    }

    void rideDetails() const override {
        cout << "\n[Premium Ride]" << endl;
        Ride::rideDetails();
        cout << "Fare: $" << fixed << setprecision(2) << fare() << endl;
    }
};

// Driver class
class Driver {
private:
    int driverID;
    string name;
    double rating;
    vector<shared_ptr<Ride>> assignedRides; // Encapsulated

public:
    Driver(int id, string name, double rating)
        : driverID(id), name(name), rating(rating) {}

    void addRide(shared_ptr<Ride> ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "\nDriver: " << name << " (ID: " << driverID << ", Rating: " << rating << ")" << endl;
        cout << "Assigned Rides:" << endl;
        for (const auto& ride : assignedRides) {
            ride->rideDetails();
        }
    }
};

// Rider class
class Rider {
private:
    int riderID;
    string name;
    vector<shared_ptr<Ride>> requestedRides;

public:
    Rider(int id, string name) : riderID(id), name(name) {}

    void requestRide(shared_ptr<Ride> ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        cout << "\nRider: " << name << " (ID: " << riderID << ")" << endl;
        cout << "Ride History:" << endl;
        for (const auto& ride : requestedRides) {
            ride->rideDetails();
        }
    }
};

int main() {
    // Create rides
    shared_ptr<Ride> ride1 = make_shared<StandardRide>(1, "Downtown", "Airport", 10);
    shared_ptr<Ride> ride2 = make_shared<PremiumRide>(2, "Uptown", "Mall", 8);

    // Demonstrate polymorphism
    vector<shared_ptr<Ride>> rideList = {ride1, ride2};
    cout << "\n--- Ride Summary (Polymorphism Demo) ---" << endl;
    for (const auto& ride : rideList) {
        ride->rideDetails();
    }

    // Assign to driver
    Driver driver(100, "Alice Johnson", 4.9);
    driver.addRide(ride1);
    driver.addRide(ride2);
    driver.getDriverInfo();

    // Rider requesting rides
    Rider rider(200, "Bob Smith");
    rider.requestRide(ride1);
    rider.requestRide(ride2);
    rider.viewRides();

    return 0;
}
