#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
struct accounts
{
 int key;
 char name[20];
 char surname[20];
 int numoffriends;
 int friends[20];
 struct accounts *left;
 struct accounts *right;
};

struct accounts *insertUser(struct accounts *,int,char[20],char[20],int,int[20]);
void inorder(struct accounts *);
struct accounts *printGreater(struct accounts *);
struct accounts *deleteUser(struct accounts *,int);
struct accounts *contains(struct accounts *);
struct accounts *friends(struct accounts *);
struct accounts *printNext(struct accounts *);
void inorder2(struct accounts *);
int searcher(struct accounts *,int);
int main(void)
{

 struct accounts *root;
 struct accounts *roottmp;
 int choice, item,item_no,i,j;
 root = NULL;
 char getname[20];
 char getsurname[20];
 int numoffriends;
 int getfriends[20];
 do
 {
  do
  {
   printf("\n 1. insertUser");
   printf("\n 2. deleteUser");
   printf("\n 3. inOrder");
   printf("\n 4. Size");
   printf("\n 5. Friends");
   printf("\n 6. Contains");
   printf("\n 7. printNext");
   printf("\n 8. printGreater");
   printf("\n 9. Exit ");
   printf("\n\t Enter choice : ");
   scanf(" %d",&choice);
   if(choice<1 || choice>9)
      printf("\n Invalid choice - try again");
  }while (choice<1 || choice>9);
  switch(choice)
  {
   case 1:
  printf("\n Enter new user key: ");
  scanf("%d", &item);
  printf("\n Enter user name: ");
  scanf("%s", getname);
  printf("\n Enter user surname: ");
  scanf("%s", getsurname);
  printf("\n Enter user friend list: ");
  scanf("%d", &i);
  for(j=0;j<i;j++){
    printf("\n %d . friend ",j+1);
    scanf("%d",&getfriends[j]);
  }
  root= insertUser(root,item,getname,getsurname,i,getfriends);
  printf("\n root is %d",root->key);

  break;
   case 2:
 printf("\n Enter the element to be deleteUsered : ");
 scanf(" %d",&item_no);
 root=deleteUser(root,item_no);

  break;
   case 3:
 printf("\n Inorder traversal of binary accounts is : ");
 inorder(root);
 break;
   case 4:
 printf("\n Size is: ");
 i=size(root);
 printf("%d",i);
 break;
   case 5:
 printf("\n Try searcher ?  ");
 printf("\n Who is gonna search ?");
 root=friends(root);
 break;
   case 6:
 printf("\n Contains ");
 root=contains(root);
 break;
   case 7:
 printf("\n printNext");
 root=printNext(root);
 break;
   case 8:
 printf("\n printGreater");
 root=printGreater(root);
   default:
  printf("\n End of program ");
   } /* end of switch */
  }while(choice !=9);
 return(0);
}

struct accounts *insertUser(struct accounts *root, int x, char name[20], char surname[20],int y, int friends[20])
{
 if(!root)
  {
    root=(struct accounts*)malloc(sizeof(struct accounts));
    root->key = x;
    root->left = NULL;
    root->right = NULL;
    strcpy(root->name,name);
    strcpy(root->surname,surname);
    root->numoffriends = y;
    memcpy(root->friends,friends,y*sizeof(int));
    return(root);
  }
  if(root->key > x)
     root->left = insertUser(root->left,x,name,surname,y,friends);
  else
   {
     if(root->key < x)
root->right = insertUser(root->right,x,name,surname,y,friends);
   }
   return(root);
 }

int size(struct accounts* root)
{
  if (root==NULL)
    return 0;
  else
    return(size(root->left) + 1 + size(root->right));
}
 void inorder(struct accounts *root)
 {
    if(root != NULL)
   {
     inorder(root->left);
     printf(" %d",root->key);
     inorder(root->right);
   }
   return;
 }
 void inorder2(struct accounts *root)
 {
    if(root != NULL)
   {
     inorder2(root->left);
     printf("\n %d",root->key);
     printf("\t %s",root->name);
     printf("\t %s",root->surname);
     printf("\n-------------------");
     inorder2(root->right);
   }
   return;
 }
 /* */
 struct accounts *deleteUser(struct accounts *ptr,int x)
 {
  struct accounts *p1,*p2;
  if(!ptr)
  {
    printf("\n Node not found ");
    return(ptr);
  }
  else
  {
     if(ptr->key < x)
     {
      ptr->right = deleteUser(ptr->right,x);
      /*return(ptr);*/
     }
     else if (ptr->key >x)
      {
       ptr->left=deleteUser(ptr->left,x);
       return ptr;
      }
      else                     /* no. 2 else */
       {
if(ptr->key == x)    /* no. 2 if */
{
 if(ptr->left == ptr->right) /*i.e., a leaf node*/
  {
   free(ptr);
   return(NULL);
  }
 else if(ptr->left==NULL)  /* a right subaccounts */
{
  p1=ptr->right;
 free(ptr);
 return p1;
}
else if(ptr->right==NULL)   /* a left subaccounts */
{
p1=ptr->left;
free(ptr);
return p1;
}
else
{
 p1=ptr->right;
 p2=ptr->right;
while(p1->left != NULL)
   p1=p1->left;
p1->left=ptr->left;
free(ptr);
return p2;
}
      }/*end of no. 2 if */
     }/* end of no. 2 else */
  /* check which path to contains for a given no. */
 }
  return(ptr);
}
/*  */
struct accounts *contains(struct accounts *root)
{

 int no,i,ino,j;
 struct accounts *ptr;
 ptr=root;
 printf("\n Enter key to search:");
 scanf(" %d",&no);
 fflush(stdin);
 while(ptr)
 {
  if(no>ptr->key)
     ptr=ptr->right;
  else if(no<ptr->key)
     ptr=ptr->left;
  else
     break;
 }
 if(ptr)
 {
  printf("\n Account with number %d is found",no);
  printf("\n Name: %s ",ptr->name);
  printf("\n Surname: %s ",ptr->surname);
  /*for(i=0;i<ptr->numoffriends;i++){
    printf("\n Friend %d is %d",i+1,ptr->friends[i]);

  }*/
 }
 else
   printf("\n Account is not exist in the system ! ",no);
 return(root);
}
int searcher(struct accounts *root,int searchbyno)
{
 int no,i,ino,j;
 struct accounts *ptr;
 ptr=root;
 no=searchbyno;
 fflush(stdin);
 while(ptr)
 {
  if(no>ptr->key)
     ptr=ptr->right;
  else if(no<ptr->key)
     ptr=ptr->left;
  else
     break;
 }
 if(ptr)
 {
    printf("\n Name: %s ",ptr->name);
    printf("\t Surname: %s \n",ptr->surname);
    return 1;
  /*printf("\n Account with number %d is found",no);

  for(i=0;i<ptr->numoffriends;i++){
    printf("\n Friend %d is %d",i+1,ptr->friends[i]);

  }*/
 }
 else{
    return 0;
   //printf("\n Account is not exist in the system ! ",no);}
   }}
struct accounts *friends(struct accounts *root)
{

 int no,i,ino,j;
 j=0;
 struct accounts *ptr;
 ptr=root;
 printf("\n Enter key to display their friends:");
 scanf(" %d",&no);
 fflush(stdin);
 while(ptr)
 {
  if(no>ptr->key)
     ptr=ptr->right;
  else if(no<ptr->key)
     ptr=ptr->left;
  else
     break;
 }
 if(ptr)
 {
  printf("\n Account with number %d is found",no);
  printf("\n Name: %s ",ptr->name);
  printf("\n Surname: %s ",ptr->surname);
  printf("\n ----EXISTING FRIENDS---");
  for(i=0;i<ptr->numoffriends;i++){
    if(searcher(root,ptr->friends[i])==1){
    //printf("\n Friend %d is %d",i+1,ptr->friends[i]);
    j++;
    }
  }
 }
 else
   printf("\n Account is not exist in the system ! ",no);
 return(root);
}
struct accounts *printNext(struct accounts *root)
{

 int no,i,ino,j;
 struct accounts *ptr;
 ptr=root;
 printf("\n Enter key to printNext:");
 scanf(" %d",&no);
 fflush(stdin);
 while(ptr)
 {
  if(no>ptr->key)
     ptr=ptr->right;
  else if(no<ptr->key)
     ptr=ptr->left;
  else
     break;
 }
 if(ptr)
 {
    inorder2(ptr);
  /*for(i=0;i<ptr->numoffriends;i++){
    printf("\n Friend %d is %d",i+1,ptr->friends[i]);

  }*/
 }
 else
   printf("\n Account is not exist in the system ! ",no);
 return(root);
}
struct accounts *printGreater(struct accounts *root)
{

 int no,i,ino,j;
 struct accounts *ptr;
 ptr=root;
 printf("\n Enter key to printNext:");
 scanf(" %d",&no);
 fflush(stdin);
 while(ptr)
 {
  if(no>ptr->key)
     ptr=ptr->right;
  else if(no<ptr->key)
     ptr=ptr->left;
  else
     break;
 }
 if(ptr)
 {
    ptr=ptr->right;
    inorder2(ptr);
  /*for(i=0;i<ptr->numoffriends;i++){
    printf("\n Friend %d is %d",i+1,ptr->friends[i]);

  }*/
 }
 else
   printf("\n Account is not exist in the system ! ",no);
 return(root);
}
