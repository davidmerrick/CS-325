/* Assignment 1 - Finding the Largest Subarray
 * Group members: David Merrick, Nick A, Taylor Friesen
 */


int main(string[] args)
{

}

string file_input()
{
  printf("Please type the filepath of the file you'd like to read: ");
  string file_name = "";
  file_name = scanf();
  if(access(file_name, F_OK) != -1){
    //the file exists
  }
  else{
    //file doesn't exist
  }
}

//this method computes pretty much every subarray individually
void close_to_zero(int arr[], int min, int max, int sum)
{
  int temp_sum;
  for(int i = 0; i < sizeof(arr); i++){
    temp_sum = 0;
    if(abs(arr[i]) < sum){
      sum = arr[i];
      min = i;
      max = i;
    }
    temp_sum = arr[i];
    for(int j = i+1; j < sizeof(arr); j++){
      temp_sum = temp_sum + arr[j];
      if(abs(temp_sum) < sum){
	sum = temp_sum;
	min = i;
	max = j;
      }
    }
  }
}

//this method computes 
