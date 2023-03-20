// A complete working C program to
// demonstrate all insertion
// methods
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>


#define NUMBER_OF_FOOD_ITEMS_PER_RESTO 2
#define MAX_NO_OF_FOOD_ORDERS 7
#define MAX_NO_OF_FOOD_ITEMS 20
#define NUMBER_OF_FOOD_LOCATIONS 9
#define NUMBER_OF_USERS 10
#define NUMBER_OF_AGENTS 10
#define NUMBER_OF_ORDERS 5

int global_order_no = 1;
int global_user_order = 1;


struct order_input{
    char user_id[20];
    char food_loc[20];
    char dish[20];
    int price;
};
struct dish_input
{
    char dish[20];
    int price;
};

struct Food_loc_input{
    char name[20];
    char address[20];
    int seats;
    char outdoor_seating[20];
    char wifi[20];
    char category[20];
    char cuisine[20];
    char area[20];
};

struct user_input{
    char user_id[20];
    char name[20];
    char phone_no[20];
    char address[100];
};

struct agent_input{
    char agent_id[20];
    char name[20];
    char phone_no[20];
    char area[20];
    int accumulated_commision;
    int on_order;
};


typedef struct date{
    int day;
    int month;
    int year;
}Date;


typedef struct dish{
    char dish[NUMBER_OF_FOOD_ITEMS_PER_RESTO][20];
    int price[NUMBER_OF_FOOD_ITEMS_PER_RESTO];
    int fav_dish[NUMBER_OF_FOOD_ITEMS_PER_RESTO];
    
}Dish;

typedef struct dish_ll{
    char dish[100];
    int price;
    int fav_dish;
    Date first_order;
    Date last_order;
    struct dish_ll* next;
    struct dish_ll* prev;
}Dish_LL;

typedef struct food{
    Dish dish;
    Dish_LL dish_ll;
    
}Food;

typedef struct Order{
    int order_no;
    char order[100];
    char agent_id[20];
    char user_id[20];
    char hotel[20];
    Date date;
    int price;
    int order_count;
    struct Order* next;
    struct Order* prev;
}Order;

typedef struct special_facilities{
    char outdoor_seating[10];//yes or no
    char wifi[10];
}Special_facilities;

typedef struct category_Node{
    char name[20];
    char address[100];
    char category[20];
    char cuisine[20];
    char area[20];
    int total_seats;
    int fav_food_location;
    int total_orders;
    Special_facilities special_facilities;
    Food menu;
    struct category_Node* prev;
    struct category_Node* next;
}Category;


typedef struct delivery_agent{
    char agent_id[20];
    char name[20];
    char phone_no[20];
    char area[20];
    int accumulated_commision;
    int on_order;
    struct delivery_agent* prev;
    struct delivery_agent* next;
    //to keep account of all orders delivered by agent use ll
}Agent;

typedef struct user{
    char user_id[20];
    char name[20];
    char phone_no[20];
    char address[100];
    Dish_LL* dish_ll;
    struct user* prev;
    struct user* next;
}User;

void food_location_input(Category** food_loc)
{
	/* 1. allocate node */
    int count = 0,k=0;
    Category* first_food_loc = *food_loc;

     FILE *fp1,*fp2; // declare a file pointer
    char filename_1[] = "food_loc_input.txt"; // name of the input file
    char filename_2[] = "dish_input.txt";


    fp1 = fopen(filename_1, "r");
    fp2 = fopen(filename_2, "r");
    
    // check if the file was opened successfully
    if (fp1 == NULL) {
        printf("Failed to open file %s\n", filename_1);
        return ;
    }

    if (fp2 == NULL) {
        printf("Failed to open file %s\n", filename_2);
        return ;
    }

    // read the input values from the file
    struct Food_loc_input table[NUMBER_OF_FOOD_LOCATIONS];
    struct dish_input dish_inp[MAX_NO_OF_FOOD_ITEMS];


    
  

    // read the table data from the file
    for (int i = 0; i < NUMBER_OF_FOOD_LOCATIONS; i++) {
        fscanf(fp1, "%s %s %d %s %s %s %s %s", table[i].name, table[i].address, &table[i].seats,table[i].outdoor_seating,table[i].wifi,table[i].category,table[i].cuisine,table[i].area);
    }

    for (int i = 0; i < MAX_NO_OF_FOOD_ITEMS; i++) {
        fscanf(fp2, "%s %d ",dish_inp[i].dish,&dish_inp[i].price);
    }

    // for (int i = 0; i < NUMBER_OF_FOOD_LOCATIONS; i++) {
    //     printf( "%s %s %d %s %s %s %s %s", table[i].name, table[i].address, table[i].seats,table[i].outdoor_seating,table[i].wifi,table[i].category,table[i].cuisine,table[i].area);
    // }

    // for (int i = 0; i < NUMBER_OF_FOOD_ITEMS; i++) {
    //     printf( "%s %d ",dish_inp[i].dish,dish_inp[i].price);
    // }


    for(int i =0 ; i< NUMBER_OF_FOOD_LOCATIONS; i++){


        Category* new_node
		= (Category*)malloc(sizeof(Category));

        count++;
	    Category* last = first_food_loc; /* used in step 5*/

   

    

	    /* 2. put in the data */
        //  printf("Enter FOOD_LOCATION name : ");
        // scanf("%s",new_node->name);
        strcpy(new_node->name,table[i].name);
        strcpy(new_node->address,table[i].address);
        new_node->total_seats = table[i].seats;
        strcpy(new_node->special_facilities.outdoor_seating,table[i].outdoor_seating);
        strcpy(new_node->special_facilities.wifi,table[i].wifi);
        strcpy(new_node->category,table[i].category);
        strcpy(new_node->cuisine,table[i].cuisine);
        // strcpy(new_node->area,table[i].area);
        int j= 0;
        while(j<NUMBER_OF_FOOD_ITEMS_PER_RESTO){
            
            strcpy(new_node->menu.dish.dish[j],dish_inp[k].dish);
            new_node->menu.dish.price[j] = dish_inp[k].price;
         
            j++;
            k++;
            

            
            // while( strcmp(dish->dish,new_node->menu.dish.dish[i]))
            // {
            //     dish = dish->next;
            // }

            // if(dish==NULL){
            //     append_dish_ll(first_dish_ll,new_node->menu.dish.dish[i],new_node->menu.dish.price[i]);
            // }
            // else
            // {
            //     printf("Dish already in global menu");
            // }
            
         
        }
       
        
       new_node->next = (*food_loc);
        new_node->prev = NULL;

        /* 4. change prev of head User to new User */
        if ((*food_loc) != NULL)
            (*food_loc)->prev = new_node;

        /* 5. move the head to point to the new User */
        (*food_loc) = new_node;
    }

 

	 fclose(fp1);
     fclose(fp2);

	return;
}

void user_input(User** first_user){


    FILE *fp1; // declare a file pointer
    char filename_1[] = "user_input.txt"; // name of the input file

    fp1 = fopen(filename_1, "r");
   
    
    // check if the file was opened successfully
    if (fp1 == NULL) {
        printf("Failed to open file %s\n", filename_1);
        return ;
    }


    // read the input values from the file
    struct user_input user_inp[NUMBER_OF_USERS];

     // read the table data from the file
    for (int i = 0; i < NUMBER_OF_USERS; i++) 
    {
         fscanf(fp1, "%s %s %s %s", user_inp[i].user_id,user_inp[i].name,user_inp[i].phone_no,user_inp[i].address);
    }


    for(int i =0 ; i < NUMBER_OF_USERS; i++)
    {
        User* new_User
		= (User*)malloc(sizeof(User));

        /* 2. put in the data */
        strcpy(new_User->user_id,user_inp[i].user_id);
        strcpy(new_User->name,user_inp[i].name);
        strcpy(new_User->phone_no,user_inp[i].phone_no);
        strcpy(new_User->address,user_inp[i].address);
        /* 3. Make next of new User as head and previous as NULL
        */
        new_User->next = (*first_user);
        new_User->prev = NULL;

        /* 4. change prev of head User to new User */
        if ((*first_user) != NULL)
            (*first_user)->prev = new_User;

        /* 5. move the head to point to the new User */
        (*first_user) = new_User;

    }

    fclose(fp1);
    return;

}

void agent_input(Agent** head_ref)
{
	/* 1. allocate Agent */

    FILE *fp1; // declare a file pointer
    char filename_1[] = "agent_input.txt"; // name of the input file



    fp1 = fopen(filename_1, "r");
   
    
    // check if the file was opened successfully
    if (fp1 == NULL) {
        printf("Failed to open file %s\n", filename_1);
        return ;
    }


    // read the input values from the file
    struct agent_input agent_inp[NUMBER_OF_AGENTS];

     // read the table data from the file
        for (int i = 0; i < NUMBER_OF_AGENTS; i++) {
            fscanf(fp1, "%s %s %s %s %d %d", agent_inp[i].agent_id,agent_inp[i].name,agent_inp[i].phone_no,agent_inp[i].area,&agent_inp[i].accumulated_commision,&agent_inp[i].on_order);
        }
    for(int i =0 ; i< NUMBER_OF_AGENTS;i++){

        Agent* new_Agent
		= (Agent*)malloc(sizeof(Agent));

       strcpy(new_Agent->agent_id,agent_inp[i].agent_id);
       strcpy(new_Agent->name,agent_inp[i].name);
       strcpy(new_Agent->phone_no,agent_inp[i].phone_no);
       strcpy(new_Agent->area,agent_inp[i].area);
       new_Agent->accumulated_commision = agent_inp[i].accumulated_commision;
       new_Agent->on_order = agent_inp[i].on_order;

        new_Agent->next = (*head_ref);
        new_Agent->prev = NULL;

        /* 4. change prev of head Agent to new Agent */
        if ((*head_ref) != NULL)
            (*head_ref)->prev = new_Agent;

        /* 5. move the head to point to the new Agent */
        (*head_ref) = new_Agent;

    }
	
}

void print_food_location_list(Category* node)
{  
    Category* last = node;
	int count = NUMBER_OF_FOOD_LOCATIONS;
	printf("\nTraversal in forward direction \n");
	while (count!=0) {
		printf("Name of FOOD_LOCATION : %s \n",node->name);
     
        // printf("Address of FOOD_LOCATION : %s\n",node->address);
            
        printf("Total no of seats : %d \n",node->total_seats);
            
        printf("Outdoor seating : %s \n",node->special_facilities.outdoor_seating);
            
        printf("wifi : %s \n",node->special_facilities.wifi);

        printf("category : %s\n ",node->category);

        printf("cusine : %s\n",node->cuisine);

        printf("area : %s\n",node->area);


        printf("--MENU-- \n");
        for(int i =0 ; i < NUMBER_OF_FOOD_ITEMS_PER_RESTO ; i++){
            printf("dish: ");
            printf("%s\n",node->menu.dish.dish[i]);  
            printf("price: ");
            printf("%d\n",node->menu.dish.price[i]);  


        }
        printf("---------------------------------------\n");

		last = node;
		node = node->next;
        count--;
	}

    

}

void print_user_list(User* user)
{
	User* last;
	printf("\nTraversal in forward direction \n");
	while (user != NULL) {
        printf("User id : %s \n",user->user_id);
		printf("Name of user : %s \n",user->name);
     
        printf("Address of user : %s\n",user->address);
            
        printf("Phone no : %s \n",user->phone_no);
            
       
        printf("---------------------------------------\n");

		last = user;
		user = user->next;
	}

}

void print_agent_list(Agent* agent){
    Agent* last;
	printf("\nTraversal in forward direction \n");
	while (agent != NULL) {
        printf("Agent id : %s \n",agent->agent_id);
		printf("Name of Agent : %s \n",agent->name);
     
        printf("Phone no : %s\n",agent->phone_no);
            
        printf("accumulated commision : %d \n",agent->accumulated_commision);
            
        printf("Phone no : %s \n",agent->phone_no);
            
       
        printf("---------------------------------------\n");

		last = agent;
		agent = agent->next;
	}
}

void search(Category** head){

    char category[20],cuisine[20],area[20];
    printf("Enter category : ");
    scanf("%s",category);

    printf("Eating locations by cusine are: ");
    Category* category_ptr = *head;
    while(category_ptr!=NULL){
        if(!strcmp(category_ptr->category,category)){
            printf("%s \n",category_ptr->name);
        }

        category_ptr = category_ptr->next;
    }

    printf("Enter cusine : ");
    scanf("%s",cuisine);
    printf("Eating locations by cusine are: ");
    category_ptr = *head;
     while(category_ptr!=NULL){
        if(!strcmp(category_ptr->cuisine,cuisine)){
            printf("%s \n",category_ptr->name);
        }

        category_ptr = category_ptr->next;
    }

    
    printf("Enter area : ");
    scanf("%s",area);
    printf("Eating locations by area are: ");
    category_ptr = *head;
     while(category_ptr!=NULL){
        if(!strcmp(category_ptr->area,area)){
            printf("%s \n",category_ptr->name);
        }

        category_ptr = category_ptr->next;
    }


}

void add_order(Order** head_ref, char order[100],int price,Date date,char agent_id[20],char user_id[20],char hotel[20])
{
    // printf("check_point_1\n");
	/* 1. allocate order */
	Order* new_order
		= (Order*)malloc(sizeof(Order));

	// Order* last = *head_ref; /* used in step 5*/

	/* 2. put in the data */
	strcpy(new_order->order,order);
    strcpy(new_order->agent_id,agent_id);
    strcpy(new_order->user_id,user_id);
    strcpy(new_order->hotel,hotel);

    new_order->order_no = global_order_no;
    new_order->price = price;
    new_order->order_count=1;

    new_order->date.day = date.day;
    new_order->date.month = date.month;
    new_order->date.year = date.year;

    // printf("%s %d:%d:%d \n",new_order->order , new_order->date.day,new_order->date.month,new_order->date.year);
    
    

	/* 3. This new order is going to be the last order, so
	// 	make next of it as NULL*/
	// new_order->next = NULL;

	/* 4. If the Linked List is empty, then make the new
		order as head */
	// if (*head_ref == NULL) {
	// 	new_order->prev = NULL;
	// 	*head_ref = new_order;
	// 	return;
	// }

	// /* 5. Else traverse till the last order */
	// while (last->next != NULL)
	// 	last = last->next;

	// /* 6. Change the next of last order */
	// last->next = new_order;

	// /* 7. Make last order as previous of new order */
	// new_order->prev = last;
        
     new_order->next = (*head_ref);
        new_order->prev = NULL;

        /* 4. change prev of head Agent to new Agent */
        if ((*head_ref) != NULL)
            (*head_ref)->prev = new_order;

        /* 5. move the head to point to the new Agent */
        (*head_ref) = new_order;

    
// printf("check_point_2\n");
	return;
}

void place_order(Category **first_food_location,Agent **first_agent,User **first_user,Order **first_order,char user_id[20],char food_location[100],char order[100],int price)
{

    Category *food_location_ptr = *first_food_location;
    Agent *agent_ptr = *first_agent;
    User *user_ptr = *first_user;
    Order* first_order_ptr = *first_order;

 
    
    


    int found_user = 0;
    while(found_user !=1 ){
        if(!strcmp((user_ptr)->user_id,user_id)){
            // printf("User exists and its id : %s\n",user_ptr->user_id);
            found_user = 1; 
        } 
       else user_ptr = (user_ptr)->next;
    }

    if(found_user == 0){
        printf("return from user");
        return;
    }


    int found_food_location = 0;
    while( found_food_location !=1)
    {  
        if(!strcmp(food_location_ptr->name,food_location))
        {   
            found_food_location = 1;
            //  printf("food location found and its name is : %s\n",food_location_ptr->name);
              for(int i = 0 ; i < MAX_NO_OF_FOOD_ITEMS ; i++)
              {
                if(!strcmp(food_location_ptr->menu.dish.dish[i],order))
                {
                    // printf("Dish found and its name is %s \n",food_location_ptr->menu.dish.dish[i]);

                    Date date;
                    // printf("The day of order : ");
                    // scanf("%d",&date.day);
                    // printf("The month of order : ");
                    // scanf("%d",&date.month);
                    // printf("The year of order : ");
                    // scanf("%d",&date.year);
                     
                     date.day = 1;
                     date.month = 1;
                     date.year = 2022;

                     int found_agent = 0;
                    while(agent_ptr->on_order == 1){
                        agent_ptr = agent_ptr->next;
                    }
                    agent_ptr->on_order = 1;

                    add_order(first_order,order,price,date,agent_ptr->agent_id,user_ptr->user_id,food_location_ptr->name);//appending order in global list
                    

                    // printf("Ordered Date : %d : %d : %d\n",user_ptr->order->date.day,user_ptr->order->date.month,user_ptr->order->date.year);
                    
    
                    // while(strcmp(user_ptr->dish_ll->dish,order) && user_ptr->dish_ll!=NULL){
                    //     user_ptr->dish_ll = user_ptr->dish_ll->next;
                    // }
                    
                    
                    // if(user_ptr->dish_ll==NULL){
                    //     add_dish_ll(&(user_ptr->dish_ll),order,price);
                    // }
                    // else
                    // {
                    //     printf("Dish already in global menu");
                    //     user_ptr->dish_ll->fav_dish++;
                    // }

                    // printf("check_point_dish_ll_1_ends\n");


                    //we will check for a free agent to deliver food
                   


                    
                    
                    
                } 
             }
        }
        else food_location_ptr = food_location_ptr->next;


       
    }

       


    // printf("Order to be delivered : %s\n",first_order_ptr->order);
    // printf("Ordered Date : %d : %d : %d\n",first_user_order_list_tra->date.day,first_user_order_list_tra->date.month,first_user_order_list_tra->date.year);
    printf("Order number  : %d\n",global_order_no);
    printf("Restaurant : %s\n",food_location_ptr->name);
    printf("User id  : %s\n",user_ptr->user_id );
    printf("Agent id : %s\n",agent_ptr->agent_id);
    printf("------------------------------\n");

    global_order_no++;

    //till here✅

                   
}

void print_global_order_list(Order** first_order){

    Order* first_order_ptr = *first_order;

    int found = 0;
     while(first_order_ptr!=NULL)
    {
        printf("Order no : %d\n",first_order_ptr->order_no);
        printf("Order : %s\n",first_order_ptr->order);
        printf("Order price : %d\n",first_order_ptr->price);
        printf("Order date : %d:%d:%d\n",first_order_ptr->date.day,first_order_ptr->date.month,first_order_ptr->date.year);
        printf("Order count : %d \n",first_order_ptr->order_count);
        printf(" %s\n",first_order_ptr->hotel);

        first_order_ptr = first_order_ptr->next;
        found = 1;
         printf("-----------------\n");
    }
   
    if(found == 0 ) printf("Order list is empty\n ");
    return;
}


void delivery(Order** first_order,Agent** first_agent, char order[100],int order_no,int price)
{
    //Delete a node in a LL
    Order *first_order_ptr = *first_order;
    Agent *first_agent_ptr = *first_agent;
	/* base case */
	if (first_order_ptr == NULL)
		return;

	/* Change next only if node to be deleted is NOT the last node */
    int found_order = 0;
    while(first_order_ptr!=NULL && found_order==0)
    {
        if(first_order_ptr->order_no == order_no && !strcmp(first_order_ptr->order,order)) found_order=1;
        else{
            first_order_ptr = first_order_ptr->next;
            // printf("Inside first_order_ptr\n");
        }
    }
    // printf("TO be Free Agent : %s \n",first_order_ptr->agent_id);

    int found_agent = 0;
    while(found_agent == 0 && first_agent_ptr != NULL)
    {
        if(!strcmp(first_agent_ptr->agent_id,first_order_ptr->agent_id)) found_agent = 1;
        else
        {
            first_agent_ptr = first_agent_ptr->next;
            // printf("Inside second_agent_ptr\n");
        } 
    }
    
    if(first_agent_ptr==NULL) printf("Delivery boy not present\n");
    else{
        first_agent_ptr->on_order = 0;
        printf("Accumulated commmision %d ",first_agent_ptr->accumulated_commision);
        first_agent_ptr->accumulated_commision += price/10;
        printf("Final Accumulated commmision %d ",first_agent_ptr->accumulated_commision);
        printf("Free Agent : %s \n",first_agent_ptr->agent_id);
    }


    //1st node
    if(first_order_ptr->next == NULL && first_order_ptr->prev == NULL){
        *first_order = NULL;
    }
    else if(first_order_ptr->next == NULL){
        //last node
        first_order_ptr->prev->next = NULL;
    }
    else{
        //general case
        first_order_ptr->prev->next = first_order_ptr->next;
        first_order_ptr->next->prev = first_order_ptr->prev;
    }
    

	/* Finally, free the memory occupied by del*/
	free(first_order_ptr);
	return;
}

void cancel_order(Order** first_order,Agent** first_agent, char order[100],int order_no,int price)
{
    //Delete a node in a LL
    Order *first_order_ptr = *first_order;
    Agent *first_agent_ptr = *first_agent;
	/* base case */
	if (first_order_ptr == NULL)
		return;

	/* Change next only if node to be deleted is NOT the last node */
    int found_order = 0;
    while(first_order_ptr!=NULL && found_order==0)
    {
        if(first_order_ptr->order_no == order_no && !strcmp(first_order_ptr->order,order)) found_order=1;
        else{
            first_order_ptr = first_order_ptr->next;
            // printf("Inside first_order_ptr\n");
        }
    }
    // printf("TO be Free Agent : %s \n",first_order_ptr->agent_id);

    int found_agent = 0;
    while(found_agent == 0 && first_agent_ptr != NULL)
    {
        if(!strcmp(first_agent_ptr->agent_id,first_order_ptr->agent_id)) found_agent = 1;
        else
        {
            first_agent_ptr = first_agent_ptr->next;
            // printf("Inside second_agent_ptr\n");
        } 
    }
    
    if(first_agent_ptr==NULL) printf("Delivery boy not present\n");
    else{
        first_agent_ptr->on_order = 0;
        // printf("Accumulated commmision %d ",first_agent_ptr->accumulated_commision);
        // first_agent_ptr->accumulated_commision += price/10;
        // printf("Final Accumulated commmision %d ",first_agent_ptr->accumulated_commision);
        printf("Free Agent : %s \n",first_agent_ptr->agent_id);
    }


    //1st node
    if(first_order_ptr->next == NULL && first_order_ptr->prev == NULL){
        *first_order = NULL;
    }
    else if(first_order_ptr->next == NULL){
        //last node
        first_order_ptr->prev->next = NULL;
    }
    else{
        //general case
        first_order_ptr->prev->next = first_order_ptr->next;
        first_order_ptr->next->prev = first_order_ptr->prev;
    }
    

	/* Finally, free the memory occupied by del*/
	free(first_order_ptr);
	return;
}

void pair_order_agent(Order** first_order){
    Order* first_order_ptr = *first_order;

    while(first_order_ptr!=NULL)
    {

        printf("%s -> %s\n",first_order_ptr->order,first_order_ptr->agent_id);
        first_order_ptr = first_order_ptr->next;

    }

    return;

}

int diff_of_days(Date date_of_order,Date date_today)
{
    Date diff;
    if(date_today.day < date_of_order.day){
        diff.day = date_today.day+30 - date_of_order.day;
        date_today.month = date_today.month - 1;
    }
    else diff.day = date_today.day - date_of_order.day;

    if(date_today.month < date_of_order.month){
        diff.month = date_today.month+12 - date_of_order.month;
        date_today.year = date_today.year - 1;
    }
    else diff.month = date_today.month - date_of_order.month;

    diff.year = date_today.year - date_of_order.year;

    return (diff.day + diff.month*30 + diff.year*365);

}

void fav_food_of_user(Order** first_order,Order** first_user_order,char user_id[20])
{

    Date date;
    date.day = 1;
    date.month = 4;
    date.year = 2022;
    Order* first_order_ptr = *first_order;
    Order* first_user_order_ptr = *first_user_order; 

    
    while(first_order_ptr != NULL )
    {
            
        // if(first_user_order_ptr==NULL){
                printf("checkpoint 1\n");
                
                if(!strcmp(first_order_ptr->user_id,user_id))
                {
                    printf("checkpoint 2\n");
                    Order* first_user_order_ptr_2 = *first_user_order;
                    
                   
                    int found_order = 0;
                    while(first_user_order_ptr_2!=NULL && found_order==0 ){

                        //  first_user_order_ptr_2->order_count = 1;
                        found_order = 0;
                        printf("checkpoint 3\n");
                        if(!strcmp(first_user_order_ptr_2->order,first_order_ptr->order) && diff_of_days(first_order_ptr->date,date)<=90 ) {
                            first_user_order_ptr_2->order_count++;
                            found_order =1;
                            printf("checkpoint 4\n");
                        }
                         first_user_order_ptr_2 = first_user_order_ptr_2->next;
                    }
                       

                    
                        if(found_order==0  && diff_of_days(first_order_ptr->date,date)<=90 ){
                        add_order(first_user_order,first_order_ptr->order,first_order_ptr->price,first_order_ptr->date,first_order_ptr->agent_id,first_order_ptr->user_id,first_order_ptr->hotel);
                        printf("checkpoint 5\n");
                    
                    }
                    
                    printf("checkpoint 6\n");
              }
              
                first_order_ptr = first_order_ptr->next;
                printf("checkpoint 7\n");
              
              
                

              
           
        // }
        // else{
            // first_user_order_ptr = first_user_order_ptr->next;
        // }
        

        

    }

    return;

}

void find_fav_restaurant(int N,Order** first_order,Order** first_hotel_order )
{
    Date date;
    date.day = 1;
    date.month = 4;
    date.year = 2022;
    Order* first_order_ptr = *first_order;
    Order* first_hotel_order_ptr = *first_hotel_order; 

    
    while(first_order_ptr != NULL )
    {
            
        // if(first_user_order_ptr==NULL){
                printf("checkpoint 1\n");
                
                // if(!strcmp(first_order_ptr->user_id,user_id))
                // {
                    printf("checkpoint 2\n");
                    Order* first_hotel_order_ptr_2 = *first_hotel_order;
                    
                   
                    int found_order = 0;
                    while(first_hotel_order_ptr_2!=NULL && found_order==0 ){

                        //  first_user_order_ptr_2->order_count = 1;
                        found_order = 0;
                        printf("checkpoint 3\n");
                        if(!strcmp(first_hotel_order_ptr_2->hotel,first_order_ptr->hotel) && diff_of_days(first_order_ptr->date,date)<=90 ) {
                            first_hotel_order_ptr_2->order_count++;
                            found_order =1;
                            printf("checkpoint 4\n");
                        }
                         first_hotel_order_ptr_2 = first_hotel_order_ptr_2->next;
                    }
                       

                    
                        if(found_order==0  && diff_of_days(first_order_ptr->date,date)<=N ){
                        add_order(first_hotel_order,first_order_ptr->order,first_order_ptr->price,first_order_ptr->date,first_order_ptr->agent_id,first_order_ptr->user_id,first_order_ptr->hotel);
                        printf("checkpoint 5\n");
                    
                    }
                    
                    printf("checkpoint 6\n");
            //   }
              
                first_order_ptr = first_order_ptr->next;
                printf("checkpoint 7\n");
              
              
                

              
           
        // }
        // else{
            // first_user_order_ptr = first_user_order_ptr->next;
        // }
        

        

    }

    return;


}

void find_fav_foods(int N,Order** first_order,Order** first_food_order){

    Date date;
    date.day = 1;
    date.month = 4;
    date.year = 2022;
    Order* first_order_ptr = *first_order;
    Order* first_hotel_order_ptr = *first_food_order; 

    
    while(first_order_ptr != NULL )
    {
            
        // if(first_user_order_ptr==NULL){
                printf("checkpoint 1\n");
                
                // if(!strcmp(first_order_ptr->user_id,user_id))
                // {
                    printf("checkpoint 2\n");
                    Order* first_food_order_ptr_2 = *first_food_order;
                    
                   
                    int found_order = 0;
                    while(first_food_order_ptr_2!=NULL && found_order==0 ){

                        //  first_user_order_ptr_2->order_count = 1;
                        found_order = 0;
                        printf("checkpoint 3\n");
                        if(!strcmp(first_food_order_ptr_2->order,first_order_ptr->order) && diff_of_days(first_order_ptr->date,date)<=90 ) {
                            first_food_order_ptr_2->order_count++;
                            found_order =1;
                            printf("checkpoint 4\n");
                        }
                         first_food_order_ptr_2 = first_food_order_ptr_2->next;
                    }
                       

                    
                        if(found_order==0  && diff_of_days(first_order_ptr->date,date)<=N ){
                        add_order(first_food_order,first_order_ptr->order,first_order_ptr->price,first_order_ptr->date,first_order_ptr->agent_id,first_order_ptr->user_id,first_order_ptr->hotel);
                        printf("checkpoint 5\n");
                    
                    }
                    
                    printf("checkpoint 6\n");
            //   }
              
                first_order_ptr = first_order_ptr->next;
                printf("checkpoint 7\n");
              
              
                

              
           
        // }
        // else{
            // first_user_order_ptr = first_user_order_ptr->next;
        // }
        

        

    }

    return;


}

Order *split(Order *head)
{
    Order *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Order *temp = slow->next;
    slow->next = NULL;
    return temp;
}

Order *merge(Order *first, Order *second)
{
    // If first linked list is empty
    if (!first)
        return second;
 
    // If second linked list is empty
    if (!second)
        return first;
 
    // Pick the smaller value
    if (first->order_count > second->order_count)
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

Order *mergeSort(Order *head)
{
    if (!head || !head->next)
        return head;
    Order *second = split(head);
 
    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);
 
    // Merge the two sorted halves
    return merge(head,second);
}

void print_area_wise_agents(Agent** first_agent,char area[100]){
    Agent* first_agent_ptr = *first_agent;

    if(*first_agent==NULL) return;
    while(first_agent_ptr!=NULL)
    {
        if(!strcmp(first_agent_ptr->area,area)) printf("%s -> %s\n",first_agent_ptr->agent_id,first_agent_ptr->name);

        first_agent_ptr = first_agent_ptr->next;
    }

    return;


}

void print_restaurant_details(Category** first_food_location,char hotel[20],char address[20]){

    Category* first_food_location_ptr = *first_food_location;

    int found_hotel = 0;
    while(first_food_location_ptr != NULL)
    {
        if(!strcmp(first_food_location_ptr->name,hotel) && !strcmp(first_food_location_ptr->address,address)){
            printf("%s -> %s\n",first_food_location_ptr->name,first_food_location_ptr->address);
            found_hotel = 1;
        } 
        
        first_food_location_ptr = first_food_location_ptr->next;
    }

    if(found_hotel==0) printf("Hotel not found\n");
    return;

}

int main()
{

	/* Start with the empty list */
	Category* first_food_location = NULL;
    Agent* first_agent = NULL;
    User* first_user=NULL;
    Order* first_order = NULL;

    Order* first_user_new_order = NULL;
    Order* first_hotel_new_order = NULL;
    Order* first_food_new_order = NULL;
    // Order* first_food_location_order_list = NULL;
    // Order* first_agent_order_list = NULL;
    // Order* first_user_order_list = NULL;
    // Dish_LL* dish_ll = NULL;


	// Insert 6. So linked list becomes 6->NULL

    food_location_input(&first_food_location);
    
    
    user_input(&first_user);
    agent_input(&first_agent);
    
	// printf("Created Resto DLL is: ");
	// print_user_list(first_user);
    // print_food_location_list(first_food_location);
    // print_user_list(first_user);
    

//     User *user_ptr = first_user;
//    while(user_ptr!=NULL){
//         user_ptr->dish_ll = NULL;
//         user_ptr = user_ptr->next;
//    }


    FILE *fp1; // declare a file pointer
    char filename_1[] = "orders.txt"; // name of the input file

    fp1 = fopen(filename_1, "r");
   
    
    // check if the file was opened successfully
    if (fp1 == NULL) {
        printf("Failed to open file %s\n", filename_1);
        return 0;
    }


    // read the input values from the file
    struct order_input order_inp[NUMBER_OF_ORDERS];
    int count =  NUMBER_OF_ORDERS;


    for(int i =0 ; i < NUMBER_OF_ORDERS ;i++)
    {

        // char user_id[20];
        // char food_loc[20];
        // char dish[20];
        // int price;

        // printf("Enter user id :");
        // scanf("%s",user_id);

        // printf("Enter food location : ");
        // scanf("%s",food_loc);

        // printf("Enter dish : ");
        // scanf("%s",dish);

        // printf("Enter price : ");
        // scanf("%d",&price);

        fscanf(fp1," %s %s %s %d ",order_inp[i].user_id,order_inp[i].food_loc,order_inp[i].dish,&order_inp[i].price);  

   }

//    for(int i =0 ; i < NUMBER_OF_ORDERS ; i++){

//      place_order( &first_food_location,&first_agent,&first_user,&first_order,order_inp[i].user_id,order_inp[i].food_loc,order_inp[i].dish,order_inp[i].price);

//    }

    // print_global_order_list(&first_order);
   
    // Order* ptr = first_order;
    //     while(ptr!=NULL){
    //         printf("ORDER NO : %d\n",ptr->order_no);
    //         ptr = ptr->next;
    //     }
    // search(&first_food_location);
    // pair_order_agent(&first_order);
    // delivery(&first_order,&first_agent,"Fried_Rice",2,120);
    // cancel_order(&first_order,&first_agent,"Fried_Rice",2,120);
    // print_global_order_list(&first_order);
    // //print_agent_list(first_agent);
    // pair_order_agent(&first_order);

    // fav_food_of_user(&first_order,&first_user_new_order,"U008");
    // // fav_food_of_user(&first_order,&first_user_new_order,"U005");
    // first_user_new_order = mergeSort(first_user_new_order);
    // print_global_order_list(&first_user_new_order);

    // find_fav_restaurant(100,&first_order,&first_hotel_new_order);
    // first_hotel_new_order = mergeSort(first_hotel_new_order);
    // print_global_order_list(&first_hotel_new_order);

    // find_fav_foods(100,&first_order,&first_food_new_order);
    // first_food_new_order = mergeSort(first_food_new_order);
    // print_global_order_list(&first_food_new_order);

    // char area[100]="North";
    // print_area_wise_agents(&first_agent,area);

    // char hotel[20]="Hotel_B";
    // char address[20]="Address_B";
    // print_restaurant_details(&first_food_location,hotel,address);
   


   
	
	return 0;
}
