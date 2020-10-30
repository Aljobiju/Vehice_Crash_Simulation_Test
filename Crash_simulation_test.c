#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int Load(void);
int Save(void);
int input_Vehicle(void);
int input_Obstacle(void);
int Vehicle_search(void);
int Obstacle_search(void);
int run_safety_test(void);
float vel_MPS(float velocity);
int Save_results(void);
int display_results(void);

int test_checked=0;

/* Vehicle Structure Definition */
struct Vehicle {
    int Vehicle_Number;
    char Vehicle_Manufracturer[20];
    char Vehicle_Name[10];
    int First_Manufractured;
    float Top_Speed;
    int Number_Of_Seats;
    float Mass;
}Vehicle_info[10];

// Obstacle Structure Definition
struct  Obstacle {
    int Obstacle_number ;
    char Obstacle_name[10] ;
    float Stopping_distance ;
}Obstacle_info[10];

struct Survival {
    float survival_rate ;
    float survival_rate_wos ;
    };

//simulation result Structure Definition
struct Simulation_result {
    int Test_id ;               //test id
    char Vehicle_name[10] ;     //Vehicle_name
    char Obstacle_name[10] ;   // Obstacle name
    int Vehicle_age ;
    float Impact_velocity ;
    int Number_of_passengers ;
    int Number_of_seatbelt_wearing_passengers ;
    float Safety_rate ;
    float Damage_rate ;
    struct Survival p_survival;
}Simulation_result_info[10];


int Vcount ; //Vehicle array size
int Ocount ; //Obstacle array size
int Scount ; //Simulation_result array size

int main(){
    int menu_input,i ;

    Load(); //Loading arrays from both files

    //Count of array
    Vcount = (sizeof(Vehicle_info) / sizeof(struct Vehicle));
    Ocount = (sizeof(Obstacle_info) / sizeof(struct Obstacle));

    //Printing vehicle info
    printf("\nDetails in Vehicle_Info :");
    printf("\n------------------------------------------------------------------------------");
    printf("\nVehicle_No||Vehicle_Manufracturer||Vehicle_Name||First_Manufractured||Top_Speed(km/h)||Number_Of_Seats||Mass(kg)");
    printf("------------------------------------------------------------------------------\n");

    for (i = 0; i < Vcount; i++)
    {
    printf("\n %d \t\t %s \t\t %s \t\t %d \t\t %.1f \t\t %d \t\t %.1f", Vehicle_info[i].Vehicle_Number, Vehicle_info[i].Vehicle_Manufracturer, Vehicle_info[i].Vehicle_Name, Vehicle_info[i].First_Manufractured, Vehicle_info[i].Top_Speed, Vehicle_info[i].Number_Of_Seats, Vehicle_info[i].Mass);
    };

    printf("\nObstacle Info");
    printf("\n|| Obstacle_Number || Obstacle_Name || Stopping_Distance ||");
    printf("\n-------------------------------------------------------------------");
    //printing obstacle info
    for(i=0;i<Ocount;i++)
    {
        printf("\n %d \t\t %s \t\t %.1f",Obstacle_info[i].Obstacle_number,Obstacle_info[i].Obstacle_name,Obstacle_info[i].Stopping_distance);
    }

    while(1){

    printf("\n\n-----------MENU--------------");
    printf("\n 1. Search a vehicle\n 2. Search an obstacle\n 3. Input/update vehicle information\n 4. Input/update obstacle information\n 5. Simulate a vehicle crash against an obstacle\n 6. Display simulation results\n 7. Save all results \n 8. Save vehicle/obstacle information\n 9. Exit");
    printf("\n-----------------------------------------------------------------");

    printf("\nEnter your option :");
    scanf("%d",&menu_input);

    switch (menu_input)
    {
    case 1 :
        // Search a vehicle
        Vehicle_search();
        break;
    case 2 :
        // Search an Obstacle
        Obstacle_search();
        break;
    case 3 :
        /* code */
        printf("\n3.Input/update vehicle information ");
        input_Vehicle();
        break;
    case 4 :
        /* code */
        printf("\n4. Input/update vehicle information ");
        input_Obstacle();
        break;
    case 5 :
        // Simulate a vehicle crash against an obstacle
        run_safety_test();
        break;
    case 6 :
        //Display simulation results
        display_results();
        break;
    case 7 :
        //Save all results
        Save_results();
        break;
    case 8 :
        // Save Vehicle & Obstacle
        Save();
        break;
    case 9 :
        /* exit */
        printf("\nThank You");
        return 0;
        exit(0);
        break;

    default:
        printf("\n---------Error---------");
        return 0;
        exit(0);
        break;
    };
}

}


//Fuction to load the array of struct from file
int Load(){

    FILE *VfileName;
    FILE *OfileName;
    VfileName = fopen("Vehicle.txt", "rb");
    if (VfileName != NULL){
        fread(Vehicle_info, sizeof(struct Vehicle), 10, VfileName);
    }
    else {
        printf("---------------Vehicle.txt file doesn't exists--------------");
    }

    OfileName = fopen("Obstacle.txt", "rb");
    if (OfileName != NULL){
        fread(Obstacle_info, sizeof(struct Obstacle), 10, OfileName);
    }
    else {
        printf("---------------Obstacle.txt file doesn't exists--------------");
    }

    return 0;
}


//Fuction to write the array of struct to file
int Save(){

    FILE *VfileName;
    FILE *OfileName;
    int Vcount, Ocount;

    //To save to vehicle.txt
    Vcount = (sizeof(Vehicle_info) / sizeof(struct Vehicle));
    VfileName = fopen ( "Vehicle.txt" , "wb" );
    fwrite (Vehicle_info, 1 , sizeof(struct Vehicle) * Vcount, VfileName );
    fclose (VfileName);

    //To save to obstacle.txt
    Ocount = (sizeof(Obstacle_info) / sizeof(struct Obstacle));
    OfileName = fopen ( "Obstacle.txt" , "wb" );
    fwrite (Obstacle_info, 1 , sizeof(struct Obstacle) * Ocount, OfileName );
    fclose (OfileName);

    printf("------Array of Objects saved to respective files------");

    return 0;
}


int input_Vehicle(){

    int Vnumber,i,index=-1;
    printf("Enter the Vehicle_Number :");
    scanf("%d",&Vnumber);
    Vcount = (sizeof(Vehicle_info) / sizeof(struct Vehicle));
    for(i=0;i<Vcount;i++){
        if (Vehicle_info[i].Vehicle_Number == Vnumber){
            index = i;
            break;
        }
    }
    if(index == -1){
        index=Vcount;
        printf("Sorry,Adding new item not implemented !!");
        return 0;
        exit(0);
    }

    printf("\n----Enter the Vehicle Info----");
    printf("\nEnter the values respectivily :\n1.Vehicle_Manufracturer\n2.Vehicle_Name\n3.First_Manufractured\n4.Top_Speed\n5.Number_Of_Seats\n6.Mass :\n");

    Vehicle_info[index].Vehicle_Number = Vnumber;

    scanf("%s %s %d %f %d %f",Vehicle_info[index].Vehicle_Manufracturer,Vehicle_info[index].Vehicle_Name,&Vehicle_info[index].First_Manufractured,&Vehicle_info[index].Top_Speed,&Vehicle_info[index].Number_Of_Seats,&Vehicle_info[index].Mass);

    Vcount = Vcount+1;
    return 0;
}


int input_Obstacle(){

    int Onumber,i,index=-1;
    printf("\nEnter the Obstacle_Number :");
    scanf("%d",&Onumber);
    Ocount = (sizeof(Obstacle_info) / sizeof(struct Obstacle));
    for(i=0;i<Ocount;i++){
        if (Obstacle_info[i].Obstacle_number == Onumber){
            index = i;
            break;
        }
    }
    if(index == -1){
        index=Ocount;
        printf("Sorry,Adding new item not implemented !!");
        return 0;
        exit(0);
    }
    Obstacle_info[index].Obstacle_number = Onumber ;
    printf("\n----Enter the Obstacle Info----");
    printf("\nEnter the values respectivily :\n1.Obstacle Name\n2.Stopping Distance :");
    scanf("%s %f",Obstacle_info[index].Obstacle_name,&Obstacle_info[index].Stopping_distance);

    Ocount=Ocount+1;

    return 0 ;

}

int Vehicle_search(){
    char Vname[10] ;
    int Vfound,i;
    Vfound=0 ;
    printf("\n1. Search a vehicle :");
    printf("\nEnter name of the vehicle to be searched :");
    scanf("%s",Vname);
    if(Vehicle_info == NULL){
        printf("\n---ERROR-Array is Empty---");
        return 0;
    }else if(strcmp(Vname,"all")==0 || strcmp(Vname,"ALL")==0){
        Vfound=1;
        ("\n------------------------------------------------------------------------------");
        printf("\nVehicle_No||Vehicle_Manufracturer||Vehicle_Name||First_Manufractured||Top_Speed(km/h)||Number_Of_Seats||Mass(kg)");
        printf("------------------------------------------------------------------------------\n");

        for (i = 0; i < Vcount; i++){
        printf("\n %d \t\t %s \t\t %s \t\t %d \t\t %.1f \t\t %d \t\t %.1f", Vehicle_info[i].Vehicle_Number, Vehicle_info[i].Vehicle_Manufracturer, Vehicle_info[i].Vehicle_Name, Vehicle_info[i].First_Manufractured, Vehicle_info[i].Top_Speed, Vehicle_info[i].Number_Of_Seats, Vehicle_info[i].Mass);
        }
    }else{

        for(i=0;i<Vcount;i++){
            if (strcmp(Vehicle_info[i].Vehicle_Name,Vname)==0)
            {
            printf("\nVehicle_No||Vehicle_Manufracturer||Vehicle_Name||First_Manufractured||Top_Speed(km/h)||Number_Of_Seats||Mass(kg)");
            printf("-----------------------------------------------------------------------------------------------------------\n");
                printf("\n %d \t\t %s \t\t %s \t\t %d \t\t %.1f \t\t %d \t\t %.1f", Vehicle_info[i].Vehicle_Number, Vehicle_info[i].Vehicle_Manufracturer, Vehicle_info[i].Vehicle_Name, Vehicle_info[i].First_Manufractured, Vehicle_info[i].Top_Speed, Vehicle_info[i].Number_Of_Seats, Vehicle_info[i].Mass);
                Vfound=1;
                break;
            }
        }
    }
    if(Vfound==0){
        printf("\n------Vehicle Not Found------");
    }
    return 0;
}

int Obstacle_search(){
    char Oname[10];
    int Ofound,i;
    Ofound=0;
    printf("\n1.Search a Obstacle :");
    printf("\nEnter name of the Obstacle to be searched :");
    scanf("%s",Oname);
    if(Obstacle_info == NULL){
        printf("\n---ERROR-Array is Empty---");
        return 0 ;
    }else if(strcmp(Oname,"all")==0 || strcmp(Oname,"ALL")==0){
        Ofound=1;
        printf("\n|| Obstacle_Number || Obstacle_Name || Stopping_Distance ||");
        printf("\n-------------------------------------------------------------------");
        //printing obstacle info
        for(i=0;i<Ocount;i++)
        {
            printf("\n %d \t\t %s \t\t %.1f",Obstacle_info[i].Obstacle_number,Obstacle_info[i].Obstacle_name,Obstacle_info[i].Stopping_distance);
        }
    }else{
        for(i=0;i<Ocount;i++){
            if (strcmp(Obstacle_info[i].Obstacle_name,Oname)==0)
            {
                printf("\n|| Obstacle_Number || Obstacle_Name || Stopping_Distance ||");
                printf("\n-------------------------------------------------------------------");
                printf("\n%d \t\t %s \t\t %.1f", Obstacle_info[i].Obstacle_number, Obstacle_info[i].Obstacle_name, Obstacle_info[i].Stopping_distance);
                Ofound=1;
                break;
            }
        }
    }
    if(Ofound==0){
        printf("\n------Obstacle Not Found------");
    }
    return 0;
}

int run_safety_test(){
    int Vnumber,Onumber,pass_no,seatbelt_no,i,Vindex,Oindex,Vage,age_factor,d_value;
    float impact_v,safety_rate,damage_rate,survival_rate_wos,survival_rate;
    while(1){
        safety_rate=1;
        Vindex = -1;
        Oindex = -1;
        printf("\nEnter the Vehicle Number to be tested :");
        scanf("%d",&Vnumber);
        printf("\nEnter the Obstacle Number to be tested :");
        scanf("%d",&Onumber);
        printf("Enter \n1. Impact_velocity \n2. Number_of_passengers \n3. Number_of_seatbelt_wearing_passengers, \n4.Vehicle_Age(yr):\n");
        scanf("%f %d %d %d",&impact_v,&pass_no,&seatbelt_no,&Vage);

        if(Vehicle_info == NULL){
            printf("\n---ERROR-Array is Empty---");
            return 0;
            continue;
        }else{
            for(i=0;i<Vcount;i++){
                if (Vehicle_info[i].Vehicle_Number == Vnumber)
                {
                    Vindex = i;
                    break;
                }
            }
        }
        if(Vindex==-1){
            printf("\n------Obstacle Not Found------");
            continue;
        }

        if(Obstacle_info == NULL){
            printf("\n---ERROR-Obstacle Array is Empty---");
            return 0;
        }else{
            for(i=0;i<Ocount;i++){
                if (Obstacle_info[i].Obstacle_number == Onumber)
                {
                    Oindex = i;
                    break;
                }
            }
        }
        if(Oindex==-1){
            printf("\n------Obstacle Not Found------");
            continue;
        }

        if((2020-Vehicle_info[Vindex].First_Manufractured)<Vage || Vage<0 || Vehicle_info[Vindex].Top_Speed < impact_v || impact_v < 0 || pass_no > Vehicle_info[Vindex].Number_Of_Seats || pass_no < 0 || seatbelt_no > pass_no || seatbelt_no < 0){
            printf("\n-----------ERROR(Invalid Input)----------------");
            continue;

        }

        if(Vage > 2){
            age_factor = 0.25 * (Vage - 2);
            safety_rate = safety_rate - (age_factor/100);
        }

        float f ;
        f= ((.5*Vehicle_info[Vindex].Mass*vel_MPS(impact_v)*vel_MPS(impact_v))/Obstacle_info[Oindex].Stopping_distance);
        safety_rate = (safety_rate-(f/10000));

        if(safety_rate <= 0){
            safety_rate = 0;
        }
        if(safety_rate >= 1){
            safety_rate = 1;
        }

        printf("\nInformational entered :");
        printf("\nImpact Velocity : %.1f \nVehicle age: %d \nNo of Passengers : %d \nNo of Passengers with seatbelt : %d",impact_v,Vage,pass_no,seatbelt_no);
        printf("\nSafety Rate : %.2f",safety_rate);
        int opt;
        printf("\nStart test (Yes:1/No:0) :");
        scanf("%d",&opt);
        if (opt==1)
        {
           break;
        }else
        {
            continue;
        }
    }
    d_value = rand() %25+1 ;
    d_value = d_value/100;
    damage_rate = d_value*(1-safety_rate);
    survival_rate = safety_rate;
    survival_rate_wos = 0;
    if(pass_no > seatbelt_no){
        survival_rate_wos = survival_rate/9;
        survival_rate = survival_rate/4;
    }

    printf("%d",&Scount);
    strcpy(Simulation_result_info[Scount].Vehicle_name,Vehicle_info[Vindex].Vehicle_Name);
    Simulation_result_info[Scount].Vehicle_age = Vage;
    Simulation_result_info[Scount].Test_id = Scount;
    Simulation_result_info[Scount].Safety_rate =safety_rate;
    Simulation_result_info[Scount].p_survival.survival_rate = survival_rate;
    Simulation_result_info[Scount].p_survival.survival_rate_wos = survival_rate_wos;
    strcpy(Simulation_result_info[Scount].Obstacle_name,Obstacle_info[Oindex].Obstacle_name);
    Simulation_result_info[Scount].Number_of_seatbelt_wearing_passengers= seatbelt_no;
    Simulation_result_info[Scount].Number_of_passengers=pass_no;
    Simulation_result_info[Scount].Impact_velocity=impact_v;
    Simulation_result_info[Scount].Damage_rate=damage_rate;


    test_checked = 1;
    printf("\n-----Test Simulation Result----");
    printf("\n\tTest ID: %d",Simulation_result_info[Scount].Test_id);
    printf("\nVehicle information:--------");
    printf("\n\tVehicle_number: %d\n\tVehicle_name: %s\n\tManufactur_date: %d\n\tTop_speed: %.1f\n\tNumber_of_seats: %d\n\tMass: %.2f",Vehicle_info[Vindex].Vehicle_Number,Vehicle_info[Vindex].Vehicle_Name, Vehicle_info[Vindex].First_Manufractured, Vehicle_info[Vindex].Top_Speed, Vehicle_info[Vindex].Number_Of_Seats, Vehicle_info[Vindex].Mass);
    printf("\nObstacle information:---------");
    printf("\n\tObstacle_number: %d\n\tObstacle_name: %s\n\t Stopping_distance: %.1f", Obstacle_info[Oindex].Obstacle_number, Obstacle_info[Oindex].Obstacle_name, Obstacle_info[Oindex].Stopping_distance);
    printf("\nTest conditions:--------------");
    printf("\n\tVehicle_age: %d\n\timpact_velocity: %.1f\n\tNumber_of_passengers: %d\n\tNumber_of_seatbelt_wearing_passengers: %d",Vage,impact_v,pass_no,seatbelt_no);
    printf("\nSimulation result:--------------");
    printf("\n\tVehicles Safety_Rate: %.4f\n\tVehicles Damage_rate: %.4f\n\tDamage_rate: %.4f\n\tPassengers Survival_rate:\n\t\tSurvival_rate (wearing seatbelts): %.4f\n\t\tSurvival__rate (not wearing seatbelts): %.4f",safety_rate,damage_rate,(1-safety_rate),survival_rate,survival_rate_wos);
    Scount = Scount + 1 ;

    return 0;
}

float vel_MPS(float velocity)
{
    float vel_MPS = (velocity*5/18);
    return vel_MPS;
}

int Save_results(){

    if(test_checked==0){
        printf("-------No Test Yet--------ERROR--------");
        return 0;
    }else
    {
        FILE *RfileName;
        int Rcount;
        //To save to Result.txt
        RfileName = fopen ( "Results.txt" , "wb" );
        fwrite (Simulation_result_info, 1 , sizeof(struct Simulation_result) * Scount, RfileName );
        fclose (RfileName);
        printf("-------RESULTS SAVED--------");
        return 0;
    }

}

int display_results(){
    char Oname[10];
    int Ofound,i;
    Ofound=0;
    printf("\n1.Display results :");
    printf("\nEnter name of the Vehicle to be displyed :");
    scanf("%s",Oname);
    if(Simulation_result_info == NULL){
        printf("\n---ERROR-Array is Empty---");
        return 0 ;
    }else if(strcmp(Oname,"all")==0 || strcmp(Oname,"ALL")==0){
        Ofound=1;
        for(i=0;i<Scount;i++){
        printf("Simulation results:--------------");
        printf("\n\tTest_id: %d\n\tVehicle_Name: %s\n\tObstacle_Name: %s\n\tVehicle_age: %d\n\tImpact_Velocity: %.2f\n\tNumber_of_passengers: %d\n\tNumber_of_seatbelt_wearing_passengers: %d\n\tSafety_rate: %.4f\n\tDamage_rate: %.4f\n\tPassengers Survival_rate: %.4f\n\t",Simulation_result_info[i].Test_id,Simulation_result_info[i].Vehicle_name,Simulation_result_info[i].Obstacle_name,Simulation_result_info[i].Vehicle_age,Simulation_result_info[i].Impact_velocity,Simulation_result_info[i].Number_of_passengers,Simulation_result_info[i].Number_of_seatbelt_wearing_passengers,Simulation_result_info[i].Safety_rate,Simulation_result_info[i].Damage_rate,Simulation_result_info[i].p_survival.survival_rate);
        }
    }else{
        for(i=0;i<Ocount;i++){
            if (strcmp(Simulation_result_info[i].Vehicle_name,Oname)==0)
            {
            printf("Simulation results:--------------");
            printf("\n\tTest_id: %d\n\tVehicle_Name: %s\n\tObstacle_Name: %s\n\tVehicle_age: %d\n\tImpact_Velocity: %.2f\n\tNumber_of_passengers: %d\n\tNumber_of_seatbelt_wearing_passengers: %d\n\tSafety_rate: %.4f\n\tDamage_rate: %.4f\n\tPassengers Survival_rate: %.4f\n\t",Simulation_result_info[i].Test_id,Simulation_result_info[i].Vehicle_name,Simulation_result_info[i].Obstacle_name,Simulation_result_info[i].Vehicle_age,Simulation_result_info[i].Impact_velocity,Simulation_result_info[i].Number_of_passengers,Simulation_result_info[i].Number_of_seatbelt_wearing_passengers,Simulation_result_info[i].Safety_rate,Simulation_result_info[i].Damage_rate,Simulation_result_info[i].p_survival.survival_rate);
            Ofound=1;
            break;
            }
        }
    }
    if(Ofound==0){
        printf("\n------Result Not Found------");
    }
    return 0;
}
