/*
  Example for handling if-statements and expressions:
  value assigned to res and printed (if supported by simulator)
*/
int main()
{
   int a,b,c,d,res;

   a=1;
   b=2;
   c=3;
   d=4;

   if (a<b)
     {
       res=(a+b+(d-c)+1)-((c-a)+(d-b)); /*res==1*/
     }
   else
     {
       res=2;
     }
	 
   print(res); /* expected value: res==1 */
}
