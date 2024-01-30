/*
 Example for handling for-loops

 main computes ISQRT(x) from lecture slides about IR:
 integer square root (truncated square root) for non-negative integer x is
 assigned to variable res and printed (if supported by simulator).
*/
int main()
{
   unsigned int i,n,m,x,res;

   /* for x value 11 is statically assigned */
   x=11;

   n=0;
   m=1;

   for (i=m; i<=x; i+=m)
     {
       n=n+1;
       m=m+2;
     }

   res=n;
   printf(res); /* expected value: res==3 */
}
