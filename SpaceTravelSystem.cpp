//Name :Ashutosh Kumar
//Roll:210221



#include<bits/stdc++.h>

using namespace std;

tm getTime(){                   //returns current rime from Operating System
    time_t now = time(0);
    tm *ltm = localtime(&now);

    ltm->tm_year=(ltm->tm_year)+1900;
    ltm->tm_mon=(ltm->tm_mon)+1;

    tm cur=*ltm;
    return cur;

} 

tm createTime(int date,int mon,int year){   //returns a struct tm with requiredd date , mon and year fields
    time_t now = time(0);
    tm *ltm = localtime(&now);
    ltm->tm_mon=mon;
    ltm->tm_year=year;
    ltm->tm_mday=date;

    tm newTime=*ltm;


    return newTime;

}


int timeDiff(tm bookingTime, tm travelDate){  // calculates the num of days difference between two given dates
    int d1,d2,m1,m2,y1,y2;

    d1=bookingTime.tm_mday;
    m1=bookingTime.tm_mon;
    y1=bookingTime.tm_year;
    d2=travelDate.tm_mday;
    m2=travelDate.tm_mon;
    y2=travelDate.tm_year;

    time_t timeA, timeB;
    struct tm tA, tB, *tptr;
    double difference;

    time(&timeA);
    time(&timeB);
    tptr = localtime(&timeA);
    tA = *tptr;
    tptr = localtime(&timeB);
    tB = *tptr;

    tB.tm_mday = d1;
    tB.tm_mon = m1-1;
    tB.tm_year = y1-1900;

    tA.tm_mday = d2;
    tA.tm_mon = m2-1;
    tA.tm_year = y2-1900;

    timeA = mktime(&tA);
    timeB = mktime(&tB);

    difference = difftime(timeA, timeB);

    int day_diff=difference/(24*60*60);

    return day_diff;
}

typedef struct Coordinates{ // stores co ordinates of a planet
    double x;
    double y;
    double z;

}Coordinates;

class planet{
    private:
    double posX;
    double posY;
    double posZ;
    string name;

    public:
        static vector<planet> Planets; // stores an array of all planets

        planet(){};

        planet(string Name,double X,double Y,double Z){
            name=Name;
            posX=X;
            posY=Y;
            posZ=Z;

            Planets.push_back(*(this));
        }

        string getName(){
            return name;
        }

        void setName(string newName){
            name=newName;
        }

        double getX(){
            return posX;
        }

        double getY(){
            return posY;
        }

        double getZ(){
            return posZ;
        }

        Coordinates getCoordiantes(){
            Coordinates current;
            current.x=posX;
            current.y=posY;
            current.z=posZ;

            return current;

        }



};

vector<planet> planet::Planets ;

class ticket{

    private:
        double price;
       
    public:

        planet leavingplanet;
        planet destplanet;
        tm timeOfBooking;
        tm dateOfTravel;

        ticket(){};
        

        ticket (planet planetA, planet planetB,tm dateTravel):leavingplanet(planetA) , destplanet(planetB),dateOfTravel(dateTravel){
            
            timeOfBooking=getTime();
            double x1=planetA.getX();
            double x2=planetB.getX();
            double y1=planetA.getY();
            double y2=planetB.getY();
            double z1=planetA.getZ();
            double z2=planetB.getZ();
            
            double dist=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
            
            double timediff=timeDiff(timeOfBooking,dateTravel);
            
            price=2000.0*dist/timediff;




        }

        double getPrice(){
            return price;
        }

        void updateSourcePlanet(planet planetA){
            leavingplanet=planetA;
        }

        void updateDestPlanet(planet planetB){
            destplanet=planetB;
        }

        bool validity(){
            tm current_time=getTime();
            int diff=timeDiff(timeOfBooking,current_time);

            if((diff/365)<=10){
                return true;
            }else{
                return false;
            }

        }


};

class traveller{
    private:
        int travellerId;
        
    public:
    
    static int createId;
        string name;
        
        traveller(){createId++;};

        traveller(string Name){
            createId++;
            travellerId=createId;
            name=Name;
        }

        void setId(int n){
            travellerId=n;
        }

        void setName(string Name){
            name=Name;
        }

        string getName(){
            return name;
        }

        int getId(){
            return travellerId;
        }


        void updateID(int newId){
            travellerId=newId;
        }

        



};

int traveller::createId =0;

class astronaut : public traveller{
    private:
    int experience;

    public:
    static vector<astronaut> list_ast;

    astronaut (string Name, int exp){
        this->setName(Name);
        this->setId(createId);
        this->experience=exp;
        list_ast.push_back(*(this));
    }



    void setExp(int newExp){
        experience=newExp;
    }

    int getExp(){
        return experience;
    }



};

vector<astronaut> astronaut::list_ast;



class commander: public traveller{
    private:
    int authority;
    public:
   

    int experience;
    int licID;
    static vector <commander> list_commander;

   

    commander(string Name,int exp){
       
        this->name=Name;
        this->setId(createId);
        this->authority=createId;
        this->experience=exp;
        this->licID=createId;
        list_commander.push_back(*(this));
    }

    int getExp(){
        return experience;
    }

};



vector <commander> commander::list_commander;

ticket createTicket();
ticket updateTicket();
bool searchOrCreateTravelClass(ticket Ticket,int id); //searches for an existing travel class with given specifications or creates a new one

class passenger:public traveller{
    private:

    bool validity;
    ticket returnjourney;

    public:

        ticket Ticket;
        bool travelClassAlloted=false;

        static vector <passenger> pass_list;
        int ticketconfirm;
        bool returnticket=false;

        passenger(string Name){
            this->name=Name;
            this->setId(createId);
            pass_list.push_back(*(this));
            this->ticketconfirm=0;
        }

        void bookTicket(){
            Ticket=createTicket();
            cout<<"price is:Rs"<<Ticket.getPrice()<<endl;
            cout<<"Want to book ticket:(Y/N)? ";
            char c;
            cin>>c;
            if(c=='Y' || c=='y'){
            this->ticketconfirm=1;
            travelClassAlloted=searchOrCreateTravelClass(Ticket,this->getId());
            cout<<"--Your ticket has been booked Successfully--"<<endl;

            }
            
        }

        void updateticket(){
            Ticket=updateTicket();
            cout<<"price is:Rs"<<Ticket.getPrice()<<endl;
            cout<<"Want to book ticket:(Y/N)? ";
            char c;
            cin>>c;
            if(c=='Y' || c=='y'){
                ticketconfirm=1;
                travelClassAlloted=searchOrCreateTravelClass(Ticket,this->getId());
                cout<<"--Ticket has been updated successfully--"<<endl;
            }
            else{ticketconfirm=0;}
        }

        

        bool verify(string Name,int id){
            if(this->getName()==Name && this->getId()==id){
                return true;
            }else{
                return false;
            }
        }

        bool TravelClass(){
            return travelClassAlloted;
        }

};

vector <passenger> passenger::pass_list;

class SpaceTravel{
    private:

    int travelId;
    
    int astId;
    int commId;

    static int Id;
    
    vector <passenger> list;//does not contain commanders and astronauts

    astronaut ast;
    commander comm;
    planet sourcePlanet;
    planet destPlanet;
    int nPass=0;

    public:

    static vector<SpaceTravel> spaceTravelList;

    tm travelDate;


    SpaceTravel(astronaut Ast,commander Comm,planet src,planet dest ,tm dateOfTravel ):comm(Comm),ast(Ast),sourcePlanet(src),destPlanet(dest),travelDate(dateOfTravel){
        Id++;
        travelId=Id;
        astId=Ast.getId();
        commId=Comm.getId();
        spaceTravelList.push_back(*(this));
        
       
    }

    planet getsrcplanet(){
        return sourcePlanet;
    }

    planet getdestplanet(){
        return destPlanet;
    }

    int getNumberPassengers(){
        return nPass;
    }

    void AddTraveller(passenger T){
        list.push_back(T);
        nPass++;
    }

    void ListAllTraveller(){
        for(auto e: list){
            cout<<e.getId()<<" "<<e.getName()<<endl;
        }
    }
    
    

};

int SpaceTravel::Id=0;

vector<SpaceTravel> SpaceTravel::spaceTravelList;

void createPass();

void createAst();

void createComm();


planet findPlanetbyName(string Name);

bool compareDates(tm t1,tm t2){
    if((t1.tm_mday)==(t2.tm_mday) && (t1.tm_mon)==(t2.tm_mon) && (t1.tm_year)==(t2.tm_year)){
        return true;
    }else{
        return false;
    }
}

int main(){

    passenger A1("pass1");
    passenger A2("pass2");
    passenger A3("pass3");
    passenger A4("pass4");
    passenger A5("pass5");
    passenger A6("pass6");
    passenger A7("pass7");
    passenger A8("pass8");
    passenger A9("pass9");
    passenger A10("pass10");
    passenger A11("pass11");
    passenger A12("pass12");
cout<<"Name and ID of existing passengers:(for checking purposes)\n";
    for(auto e:passenger::pass_list){
        cout<<"Name:"<<e.getName()<<" ID:"<<e.getId()<<endl;
    }

    planet mars("mars",0,0,3);
    planet earth("earth",0,4,0);
    planet moon("moon",0,5,0);

    commander D("comm1",10);
    commander E("comm2",10);

    astronaut F("ast1",12);
    astronaut G("ast2",13);

    while(true){
        cout<<"  What you want to do?\n";
        cout<<"  Create New Passenger: Enter 1\n";
        cout<<"  Book Ticket: Enter 2\n";
        cout<<"  Update Ticket: Enter 3\n";
        cout<<"  Register new Astronaut : Enter 4\n";
        cout<<"  Register new Commander : Enter 5\n";
        int n;
        cin>>n;
        if(n==1){
            createPass();
        }else if(n==2){
            cout<<"  Enter your Name:";
            string Name;
            cin>>Name;
            cout<<"  Enter your id:";
            int id;
            cin>>id;
            int found=0;
            for(auto e:passenger::pass_list){
                if(e.verify(Name,id)==1){
                    found=1;
                    e.bookTicket();
                    break;
                }
            }
            if(!found){
                cout<<"  Given Name and Id do not match :(\n";
            }
        }else if(n==3){
            cout<<"  Enter your Name:";
            string Name;
            cin>>Name;
            cout<<"  Enter your id:";
            int id;
            cin>>id;
            int found=0;
            for(auto e:passenger::pass_list){
                if(e.verify(Name,id)==1){
                    found=1;
                    e.updateticket();
                    break;
                }
            }
            if(!found){
                cout<<"  Given Name and Id do not match :(\n";
            }
        }else if(n==4){
            createAst();
        }else if(n==5){
            createComm();
        }
        else{break;}
        cout<<"  Want to exit?(Y/N)";
        char c;
        cin>>c;
        if(c=='Y' || c=='y'){
            break;
        }else{
            cout<<"===================================="<<endl;
        }
    }

    return 0;
}


void createPass(){
    cout<<"Enter Name(use underscore or dash instead of space):\n";

    string Name;
    cin>>Name;


    passenger A(Name);
    cout<<"Your Name is "<<Name<<" and id is "<<A.getId()<<endl; 

}

void createAst(){           //registers a new astronaut
    cout<<"Enter Name of The Astronaut:";
    string Name;
    cin>>Name;
    cout<<endl;
    cout<<"Enter Experience(int):";
    int exp;
    cin>>exp;

    astronaut A(Name,exp);
    

}

void createComm(){      //registers a new commandder

    cout<<"Enter Name of The Commander:";
    string Name;
    cin>>Name;
    cout<<endl;
    cout<<"Enter Experience(int):";
    int exp;
    cin>>exp;

    commander A(Name,exp);
}


planet findPlanetbyName(string Name){ //returns planet whose name is provided (it is assumed that different planets have different names)
    planet found;

    for(auto e:planet::Planets){
        if(e.getName()==Name){
            found=e;
        }
    }

    return found;
}

ticket createTicket(){
    cout<<"Enter Source Planet:(mars,earth,moon)(type):";
    string src;
    cin>>src;
    cout<<"Enter Destination Planet:(mars,earth,moon)(type):";
    string dest;
    cin>>dest;

    planet A;
    planet B;

    A=findPlanetbyName(src);
    B=findPlanetbyName(dest);

    int day,mon,yr;
    cout<<"Enter date of travel\n day:";
    cin>>day;
    cout<<"month:";
    cin>>mon;
    cout<<"Year:";
    cin>>yr;

    tm newtime=createTime(day,mon,yr);
    ticket newticket(A,B,newtime);
    return newticket;

}

ticket updateTicket(){
    cout<<"Enter new Source Planet:(mars,earth,moon)(type)";
    string src;
    cin>>src;
    cout<<"Enter new Destination Planet:(mars,earth,moon)(type)";
    string dest;
    cin>>dest;

    planet A;
    planet B;

    A=findPlanetbyName(src);
    B=findPlanetbyName(dest);

    int day,mon,yr;
    cout<<"Enter new date of travel\n day:";
    cin>>day;
    cout<<"month:";
    cin>>mon;
    cout<<"Year:";
    cin>>yr;

    tm newtime=createTime(day,mon,yr);

    ticket newticket(A,B,newtime);

    return newticket;

}

bool searchOrCreateTravelClass(ticket Ticket,int id){
    int found=0;

    for(auto e:SpaceTravel::spaceTravelList){
        if(e.getdestplanet().getName()==Ticket.destplanet.getName() && e.getsrcplanet().getName()==Ticket.leavingplanet.getName() && compareDates(e.travelDate,Ticket.dateOfTravel) ){
            if(e.getNumberPassengers()>=10){
                continue;
            }else{
                found=1;
                for(auto p:passenger::pass_list){
                    if(p.getId()==id){
                        e.AddTraveller(p);
                    }
                }
                return true;
            }

        }
    }

    if(!found){
        vector <passenger> temp;

        for(auto e:passenger::pass_list){
           
            if(e.ticketconfirm==1){
                
                if(e.Ticket.destplanet.getName()==Ticket.destplanet.getName() && e.Ticket.leavingplanet.getName()==Ticket.leavingplanet.getName() && compareDates(e.Ticket.dateOfTravel,Ticket.dateOfTravel) ){
                    temp.push_back(e);
                }
            }
        }

        cout<<temp.size()<<endl;

        if(temp.size()<=2){
            return false;

        } else{

            SpaceTravel space(astronaut::list_ast[0],commander::list_commander[0],Ticket.leavingplanet,Ticket.destplanet,Ticket.dateOfTravel);

            for(auto e: temp){
                space.AddTraveller(e);
                e.travelClassAlloted=true;
            }

            return true;


        }
    }
    return false;
}
