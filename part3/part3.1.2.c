//Trying to create some sort of data structure that can store the table and store for each table
//
const int MAX_GROUP_SIZE = 8; //The maximum number of people in a group that is allowed
const int MAX_TIME_DURATION = 100; //The maximum number of seconds that is avaliable

struct {
    //Change any of the types to be the right types of the programming problem
    int arriving_time = 0;//Possibly the place the store the group arrival time (Time when corresponding system call is invoked)
    int group_id = 0; //This is the integer identify the group
    int num_of_customers = 0; //Number of customers in a group
    int stay_duration = 0; //The duration of how the long the group stays in the bar
    int spending = 0; //How much money is earned by the bar
    int waiting_time = 0; //The maximum time that the group will wait for the seats, if there is not seats available


} customer_group;