"Define the Ride class"
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance |

    Ride class >> newWith: id pickup: pickup dropoff: dropoff distance: dist [
        ^ (self new)
            setId: id pickup: pickup dropoff: dropoff distance: dist
    ]

    setId: id pickup: pickup dropoff: dropoff distance: dist [
        rideID := id.
        pickupLocation := pickup.
        dropoffLocation := dropoff.
        distance := dist.
        ^self
    ]

    fare [
        self subclassResponsibility
    ]

    rideDetails [
        ^ 'Ride ID: ', rideID printString, ' | Pickup: ', pickupLocation, ' | Dropoff: ', dropoffLocation, ' | Distance: ', distance printString, ' miles'
    ]
]

"StandardRide"
Ride subclass: StandardRide [
    fare [
        ^ distance * 1.5
    ]

    rideDetails [
        ^ '[Standard Ride] ', super rideDetails, ' | Fare: $', (self fare printString)
    ]
]

"PremiumRide"
Ride subclass: PremiumRide [
    fare [
        ^ (distance * 3.0) + 5.0
    ]

    rideDetails [
        ^ '[Premium Ride] ', super rideDetails, ' | Fare: $', (self fare printString)
    ]
]

"Driver class"
Object subclass: Driver [
    | driverID name rating assignedRides |

    Driver class >> newWith: id name: n rating: r [
        ^ (self new) setId: id name: n rating: r
    ]

    setId: id name: n rating: r [
        driverID := id.
        name := n.
        rating := r.
        assignedRides := OrderedCollection new.
        ^self
    ]

    addRide: ride [
        assignedRides add: ride
    ]

    getInfo [
        | out |
        out := 'Driver: ', name, ' (ID: ', driverID printString, ', Rating: ', rating printString, ')\nAssigned Rides:\n'.
        assignedRides do: [:r | out := out, r rideDetails, '\n'].
        ^out
    ]
]

"Rider class"
Object subclass: Rider [
    | riderID name requestedRides |

    Rider class >> newWith: id name: n [
        ^ (self new) setId: id name: n
    ]

    setId: id name: n [
        riderID := id.
        name := n.
        requestedRides := OrderedCollection new.
        ^self
    ]

    requestRide: ride [
        requestedRides add: ride
    ]

    viewRides [
        | out |
        out := 'Rider: ', name, ' (ID: ', riderID printString, ')\nRide History:\n'.
        requestedRides do: [:r | out := out, r rideDetails, '\n'].
        ^out
    ]
]

"Main demo"
| ride1 ride2 driver rider |

ride1 := StandardRide newWith: 1 pickup: 'Downtown' dropoff: 'Airport' distance: 10.
ride2 := PremiumRide newWith: 2 pickup: 'Uptown' dropoff: 'Mall' distance: 8.

"Polymorphism demo"
'--- Ride Summary (Polymorphism Demo) ---' displayNl.
ride1 rideDetails displayNl.
ride2 rideDetails displayNl.

driver := Driver newWith: 100 name: 'Alice' rating: 4.9.
driver addRide: ride1.
driver addRide: ride2.
driver getInfo displayNl.

rider := Rider newWith: 200 name: 'Bob'.
rider requestRide: ride1.
rider requestRide: ride2.
rider viewRides displayNl.
