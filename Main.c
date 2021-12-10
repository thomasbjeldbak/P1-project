#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include "CarRentalFunctions.h"

carRenter     carRenterData();
carOwner      carOwnerData();
carRenter     enterCarRenter();
carOwner      enterCarOwner();
carRenter     carRenterDisplay(carRenter carRenter1);
carOwner      carOwnerDisplay(carOwner carOwner1);
carRenter     carRenterEdit(carRenter carRenter1);
carOwner      carOwnerEdit(carOwner carOwner1);
carRenter     carRenterSelect(char Email[]);
carOwner      carOwnerSelect(char Email[]);
int           userSelect(char Email[]);
void          carSelect(carOwner arrCars[]);
int           compare_type_and_price(const void *v1, const void *v2);
int           compare_rating(const void *v1, const void *v2);

int main(void) {
    int answer = 0;
    int isRenter = -1;
    char Email[50];

    carOwner arrCars[10];

    srand(time(NULL));

    printf("1. Sign in\n2. Sign up\n");
    do{
      scanf("%d", &answer);  
    } while(answer < 1 && answer > 2);

    if(answer == 1){

      do{
        printf("Please enter your email: ");
        scanf("%s", &Email); 

        isRenter = userSelect(Email); 
      } while(isRenter < 0);
      
      if(isRenter == 1){
        carRenter1 = carRenterSelect(Email);
        printf("Welcome back %s!\n", carRenter1.name);
        
        printf("1. Rent a car\n2. View your profile\n3. Edit your profile\n4. Rate your latest Rental\n");
        do{
          scanf("%d", &answer);  
        } while(answer < 1 && answer > 4);

        switch (answer) {
          case 1:
            carSelect(arrCars);
            break;
          
          case 2:
            carRenterDisplay(carRenter1);
            break;

          case 3:
            carRenterEdit(carRenter1);
            break;
          
          case 4:
            findTransaction();
            break;
          
          default:
            break;
        }
      }
      else if(isRenter == 0) {
        carOwner1 = carOwnerSelect(Email);
        printf("Welcome back %s!\n", carOwner1.name);

        printf("1. View your car rental history\n2. View your profile\n3. Edit your profile\n4. Rate your latest Rental\n");
        do{
          scanf("%d", &answer);  
        } while(answer < 1 && answer > 4);

        switch (answer) {
          case 1:
            break;
          
          case 2:
            carOwnerDisplay(carOwner1);
            break;

          case 3:
            carOwnerEdit(carOwner1);
            break;
          
          case 4:
            findTransaction();
            break;

          default:
            break;
        }
      }
    }
    else if(answer == 2){
      printf("1. Sign up as renter\n2. Sign up as owner\n");
      do{
        scanf("%d", &answer);  
      } while(answer < 1 && answer > 2);      

      if(answer == 1){
        carRenterData();
      }
      else if(answer == 2){
        carOwnerData();
      }
    }
    return 0;
}

//The function that fetches data for a car renter
carRenter carRenterData() {
    FILE *fp;
    carRenter tempCarRenter;
    
    tempCarRenter = enterCarRenter();

    // open file for writing
    fp = fopen ("renters.dat", "a");
    if (fp == NULL){
      fprintf(stderr, "\nError opened file\n");
      exit (1);
    }
    
    // write struct to file
    fwrite (&tempCarRenter, sizeof(tempCarRenter), 1, fp);

    if(fwrite != 0)
      printf("Account succesfully created !\n");
    else
      printf("Error writing to file !\n");
 
    // close file
    fclose (fp);
}

//The function that fetches data for a car owner
carOwner carOwnerData() {
    FILE *fp;
    carOwner tempCarOwner;

    tempCarOwner = enterCarOwner();

    // open file for writing
    fp = fopen ("owners.dat", "a");
    if (fp== NULL){
      fprintf(stderr, "\nError opened file\n");
      exit (1);
    }
    
    // write struct to file
    fwrite (&tempCarOwner, sizeof(tempCarOwner), 1, fp);

    if(fwrite != 0)
      printf("Account succesfully created !\n");
    else
      printf("Error writing to file !\n");
 
    // close file
    fclose (fp);
}

carRenter enterCarRenter(void) {
  carRenter tempCarRenter;
  char name[50];
  
  tempCarRenter.ID = ((rand() % 1000000) + 100000);
  printf("Enter name: ");
  fgets(tempCarRenter.name, 50, stdin);
  getName(name);
  strcpy(tempCarRenter.name, name);
  printf("Enter phone number: ");
  scanf(" %s", &tempCarRenter.phoneNum);
  printf("Enter E-mail: ");
  scanf(" %s", &tempCarRenter.Email);
  printf("Enter age: ");
  scanf(" %d", &tempCarRenter.age);
  printf("Enter postcode: ");
  do {
    scanf("\n%d", &tempCarRenter.postCode);
  } while(tempCarRenter.postCode != 9000 && tempCarRenter.postCode != 9200 && tempCarRenter.postCode != 9210 && tempCarRenter.postCode != 9220);
  printf("Enter preferred type of car (a: city car/hatchback, b: sedan/station car, c: SUV/Van): ");
  scanf(" %c", &tempCarRenter.prefCarType);
  printf("Enter preferred transmission type (a = automatic, b = manual,  c = both)): ");
  scanf(" %c", &tempCarRenter.prefTransmissionType);
  tempCarRenter.rating = 0;
  tempCarRenter.ratingAmount = 0;
  return tempCarRenter;
}

carOwner enterCarOwner(void) {
  carOwner tempCarOwner;
  char name[50];

  tempCarOwner.ID = ((rand() % 1000000) + 100000);
  printf("Enter name: ");
  fgets(tempCarOwner.name, 50, stdin);
  getName(name);
  strcpy(tempCarOwner.name, name);
  printf("Enter phone number: ");
  scanf(" %s", &tempCarOwner.phoneNum);
  printf("Enter E-mail: ");
  scanf(" %s", &tempCarOwner.Email);
  printf("Enter age: ");
  scanf(" %d", &tempCarOwner.age);
  printf("Enter postcode: ");
  do {
    scanf("\n%d", &tempCarOwner.postCode);
  } while(tempCarOwner.postCode != 9000 && tempCarOwner.postCode != 9200 && tempCarOwner.postCode != 9210 && tempCarOwner.postCode != 9220);
  printf("Enter how much your car should cost per hour: ");
  scanf(" %d", &tempCarOwner.price);
  
  while(tempCarOwner.price > 100) {
    printf("\nEnter a maximum of 100 dkk: ");
    scanf(" %d", &tempCarOwner.price);
  }

  printf("Enter name of your car: ");
  fgets(tempCarOwner.carName, 50, stdin);
  getName(name);
  strcpy(tempCarOwner.carName, name);
  printf("Enter car type (a: city car/hatchback, b: sedan/station car, c: SUV/Van): ");
  tempCarOwner.carType = getchar();
  printf("Enter your car's model year: ");
  scanf(" %d", &tempCarOwner.modelYear);
  printf("Enter your car's mileage: ");
  scanf(" %d", &tempCarOwner.odometer);
  printf("Enter your car's transmission type (a = automatic, b = manual): ");
  scanf(" %c", &tempCarOwner.transmission);
  printf("Enter small description of car: ");
  fgets(tempCarOwner.CarDescription, 50, stdin);
  getName(name);
  strcpy(tempCarOwner.CarDescription, name);
  tempCarOwner.rating = 0;
  tempCarOwner.ratingAmount = 0;
  return tempCarOwner;
}

int userSelect(char Email[]){
    FILE *fp, *fp1;
    carRenter tempCarRenter;
    carOwner tempCarOwner;
    int found = 0;
    
    // Open renters.dat for reading
    fp = fopen ("renters.dat", "rb");
    if (fp == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }
    // Open owners.dat for reading
    fp1 = fopen ("owners.dat", "rb");
    if (fp1 == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }

    // read file contents till end of file
    while(1){
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);    
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarRenter.Email, Email)){
        found = 1;
        RenterLoggedIn = 1;
        fclose(fp);
        fclose(fp1);
        return 1;
      }	
    }

    while(1){
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);    
      if(feof(fp1)){
        break;
      }
      if(!strcmp(tempCarOwner.Email, Email)){
        found = 1;
        OwnerLoggedIn = 1;
        fclose(fp);
        fclose(fp1);        
        return 0; 
      }	
    }    

    if(found == 0){
      printf("Sorry no record found\n");
    }

    // close file
    fclose (fp);   
    fclose (fp1); 
    return -1;
}

carRenter carRenterSelect(char Email[]){
    FILE *fp;
    carRenter tempCarRenter;
    int found = 0;

    // Open renters.dat for reading
    fp = fopen ("renters.dat", "rb");
    if (fp == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }
 
    // read file contents till end of file
    while(1){
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);    
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarRenter.Email, Email)){
        found = 1;  
        break;
      }	
    }
    if(found == 0){
      printf("Sorry no record found\n");
    }
    // close file
    fclose (fp);    
    return tempCarRenter;
}

carOwner carOwnerSelect(char Email[]){
    FILE *fp;
    carOwner tempCarOwner;
    int found = 0;

    // Open owners.dat for reading
    fp = fopen ("owners.dat", "rb");
    if (fp == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }

    // read file contents till end of file
    while(1){
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);    
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarOwner.Email, Email)){
        found = 1; 
        break; 
      }	
    }
    if(found == 0){
      printf("Sorry no record found\n");
    }
    // close file
    fclose (fp);    
    return tempCarOwner;
}

carRenter carRenterDisplay(carRenter carRenter1){

    printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nPreferred car type: %c\nPreferred transmission type: %c\nRating: %0.2lf (%d Ratings)\n",
    carRenter1.name, carRenter1.phoneNum, carRenter1.Email, carRenter1.age, carRenter1.postCode, carRenter1.prefCarType, carRenter1.prefTransmissionType, carRenter1.rating, carRenter1.ratingAmount);   

}

carOwner carOwnerDisplay(carOwner carOwner1){

  printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nCar price: %d dkk per hour\nCar name: %s\nModel year: %d\nKilometers driven: %d\nTransmission type: %c\nDescription: %s\nRating: %0.2lf (%d ratings)",
  carOwner1.name, carOwner1.phoneNum, carOwner1.Email, carOwner1.age, carOwner1.postCode, carOwner1.price, carOwner1.carName, carOwner1.modelYear, carOwner1.odometer, carOwner1.transmission, carOwner1.CarDescription, carOwner1.rating, carOwner1.ratingAmount);   

}

carRenter carRenterEdit(carRenter carRenter1){
    FILE *fp, *fp1;
    carRenter tempCarRenter;
    int found = 0;

    fp = fopen("renters.dat","rb");
    fp1 = fopen("temp.dat","wb");

    while(1){
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarRenter.Email, carRenter1.Email)){
        found = 1;
        enterCarRenter();
        fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
      }
      else{
        fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
      }
    }
    fclose(fp);
    fclose(fp1);

    if(found == 0){
      printf("Sorry, no record found");
    }
    else{
      fp = fopen("renters.dat","wb");
      fp1 = fopen("temp.dat","rb");

      while(1){
        fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);

        if(feof(fp1)){
          break;
        }
        fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
      }
    }
    fclose(fp);
    fclose(fp1);    
}

carOwner carOwnerEdit(carOwner carOwner1){
    FILE *fp, *fp1;
    carOwner tempCarOwner;
    int found = 0;

    fp = fopen("owners.dat","rb");
    fp1 = fopen("temp.dat","wb");

    while(1){
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarOwner.Email, carOwner1.Email)){
        found = 1;
        tempCarOwner = enterCarOwner();
        fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
      }
      else{
        fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
      }
    }
    fclose(fp);
    fclose(fp1);

    if(found == 0){
      printf("Sorry, no record found");
    }
    else{
      fp = fopen("owners.dat","wb");
      fp1 = fopen("temp.dat","rb");

      while(1){
        fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);

        if(feof(fp1)){
          break;
        }
        fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
      }
    }
    fclose(fp);
    fclose(fp1);    
}

void carSelect(carOwner arrCars[]){
    FILE *fp;
    carOwner tempCarOwner;
    int i = 0, number_of_cars, choice, rent_car;

    fp = fopen ("owners.dat", "rb");
    if (fp == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }

    while(1){
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
      if(feof(fp)){
        number_of_cars = i;
        break;
      }
      
      arrCars[i] = tempCarOwner;
      i++;
    }

    qsort(arrCars, number_of_cars, sizeof(carOwner), compare_type_and_price);

    do
    {
      for(i = 0; i < number_of_cars; i++){
        printf("\n%d.", i + 1);
        printf("\nPrice: %d\nCar name: %s\nCar type: %c\nModel year: %d\nOdometer: %d\nTransmission type: %c\nCar description: %s\nCar is located in: %d\n", 
        arrCars[i].price, arrCars[i].carName, arrCars[i].carType, arrCars[i].modelYear, arrCars[i].odometer, arrCars[i].transmission, arrCars[i].CarDescription, arrCars[i].postCode);
      }

      printf("\nChoose which car you would like to rent: ");
      scanf(" %d", &choice);

      choice = choice - 1;

      printf("\nPrice: %d\nCar name: %s\nCar type: %c\nModel year: %d\nOdometer: %d\nTransmission type: %c\nCar description: %s\nCar is located in: %d\n", 
      arrCars[choice].price, arrCars[choice].carName, arrCars[choice].carType, arrCars[choice].modelYear, arrCars[choice].odometer, arrCars[choice].transmission, arrCars[choice].CarDescription, arrCars[choice].postCode);

      printf("\nWould you like to rent this car? (1 = Yes, 2 = No): ");
      scanf(" %d", &rent_car);

      if (rent_car == 1)
      {
        printf("You successfully chose %s\n", arrCars[choice].carName);
        makeDeal(arrCars[choice]);
      }
    } while (rent_car != 1);
    
    fclose(fp);
}

int compare_type_and_price(const void *v1, const void *v2){ 
    const carOwner *p1 = (carOwner *)v1;
    const carOwner *p2 = (carOwner *)v2;
    if (p1->carType < p2->carType)
    {
      return -1;
    }
    else if (p1->carType > p2->carType)
    {
      return 1;
    }
    else if (p1->price < p2->price)
        return -1;
    else if (p1->price > p2->price)
        return 1;
    else
        return 0;
}

int compare_rating(const void *v1, const void *v2){ 
    const carOwner *p1 = (carOwner *)v1;
    const carOwner *p2 = (carOwner *)v2;
    if (p1->rating < p2->rating)
        return -1;
    else if (p1->rating > p2->rating)
        return 1;
    else
        return 0;
}