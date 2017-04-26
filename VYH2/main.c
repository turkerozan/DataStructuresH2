/*
@author: Ozan T.Demir
last review date: 01 apr 17
code avaible at: github.com/turkerozan/vyh2
*/
#include<conio.h>
#include<stdio.h>
struct accounts
{
    int key;
    char name[20];
    char surname[20];
    int numoffriends;//int that saves how many friends that account has
    int friends[20];
    struct accounts *left;
    struct accounts *right;
};
//Function Declarations
struct accounts *insertUser(struct accounts *,int,char[20],char[20],int,int[20]);//to insert account to tree
void inorder(struct accounts *);//to print inorder
struct accounts *printGreater(struct accounts *);//to print greater than what we give
struct accounts *deleteUser(struct accounts *,int);//to delete users from tree
struct accounts *contains(struct accounts *);//to see if people is here
struct accounts *friends(struct accounts *);//to see if people's friends is here
struct accounts *printNext(struct accounts *);//to print just subtree of given account
void inorder2(struct accounts *);//its the same as inorder but it also include details of nodes to print
int searcher(struct accounts *,int);
//function declaration end
int main(void)
{
    struct accounts *root;//we need to declare root
    struct accounts *roottmp;//in order to print subtree or given node, we need to behave that node as root, so it is temp. root
    int choice; // for menu choice
    int key;//inside struct key value
    int i,j;//for iteration purposes
    root = NULL;//first root is null
    char getname[20];//inside struct name
    char getsurname[20];//inside struct surname
    int numoffriends;//inside struct also
    int getfriends[20];//friend list of struct
    do //do sth until choice is 9
    {
        do //menu starts
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
                printf("\n Wrong choice");
        }
        while (choice<1 || choice>9);
        switch(choice)
        {
        case 1://so for insert user, we need to get values from user;
            printf("\n Enter new user key: ");
            scanf("%d", &key);
            printf("\n Enter user name: ");
            scanf("%s", getname);
            printf("\n Enter user surname: ");
            scanf("%s", getsurname);
            printf("\n Enter user # of friends: ");
            scanf("%d", &i);
            for(j=0; j<i; j++)
            {
                printf("\n %d . friend ",j+1);
                scanf("%d",&getfriends[j]);
            }
            root= insertUser(root,key,getname,getsurname,i,getfriends); // send values to insertUser for inserting to tree
            break;
        case 2:
            printf("\n Enter the account key to be deleted : ");//for delete user, only need for us is key
            scanf(" %d",&key);
            root=deleteUser(root,key);//send key to funtion
            break;
        case 3:
            printf("\n Inorder : ");
            inorder2(root);
            break;
        case 4:
            printf("\n Size is: ");
            i=size(root);
            printf("%d",i);
            break;
        case 5:
            printf("\n Whos friend should I show?");
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
    }
    while(choice !=9);
    return(0);
}
/*
so for insertUser function, we need root to determine where we are;
and values to insert which node will carry such as name , surname etc.
here x is just key of node
y is number of friends
friends array is composed of integer (account keys)

*/
struct accounts *insertUser(struct accounts *root, int x, char name[20], char surname[20],int y, int friends[20])
{
    if(!root) // if we reach the node which is free to get values
    {
        root=(struct accounts*)malloc(sizeof(struct accounts)); //dynamically allociate memory for root
        root->key = x; // x was sent by user in menu
        root->left = NULL; //this is kind of newly created node so right and left dont have anythnig to show
        root->right = NULL;
        strcpy(root->name,name); //basic copy funtion to copy name to inside node
        strcpy(root->surname,surname);
        root->numoffriends = y;
        memcpy(root->friends,friends,y*sizeof(int));//memcpy funtion to copy
        //number of friends(y) * size of int amount of data to friends
        return(root);
    }
    if(root->key > x)//if key is less than our root, than iterate to left,make root that iterated node
        root->left = insertUser(root->left,x,name,surname,y,friends);
    else
    {
        if(root->key < x)//if key is greater than our root, iterate to right, make root that iterated node
            root->right = insertUser(root->right,x,name,surname,y,friends);
    }
    return(root);
}

int size(struct accounts* root)//size function just need root so it will reach all of the tree
{
    if (root==NULL)//if reached node is null, than go back,it is recursive function
        return 0;
    else
        return(size(root->left) + 1 + size(root->right));//what is just basically do is , get node recursively until it reaches leafs
}
void inorder(struct accounts *root)//this function just prints keys, its for debug purpose
{
    if(root != NULL)//for stop variable, its recursive
    {
        inorder(root->left); // LNR read
        printf(" %d \t",root->key);
        inorder(root->right);
    }
    return;
}
void inorder2(struct accounts *root) // this function not only prints keys, but also all details we need to display
{
    if(root != NULL)
    {
        inorder2(root->left); //first get leftest node, than node(because it is the leftest one after this) than go right
        printf("\n %d",root->key);
        printf("\t %s",root->name);
        printf("\t %s",root->surname);
        printf("\n-------------------");
        inorder2(root->right);
    }
    return;
}
/*
x represents as key, ptr is root firstly
*/
struct accounts *deleteUser(struct accounts *ptr,int x)
{
    struct accounts *p1,*p2;
    if(ptr==NULL)
    {
        printf("\n Node delete error #1");
        return(ptr);//it is possible to root is selected which is null
    }
    else
    {
        if(ptr->key < x)
        {
            ptr->right = deleteUser(ptr->right,x);
        }
        else if (ptr->key >x)
        {
            ptr->left=deleteUser(ptr->left,x);
            return ptr;
        }
        else //End of iteration until we found the key
        {
            if(ptr->key == x)
            {
                if(ptr->left == ptr->right) // if key is on the bottom just free it
                {
                    free(ptr);
                    return(NULL);
                }
                else if(ptr->left==NULL)  // if node is in middle and no left node, we have to delete it and replace with right
                {
                    p1=ptr->right;
                    free(ptr);
                    return p1;
                }
                else if(ptr->right==NULL) // if node is in middle and has no right node, delete it, and replace it with left one
                {
                    p1=ptr->left;
                    free(ptr);
                    return p1;
                }
                else // if node has right and left(for ex. root node, iterate until leftest node and merge with right one
                {
                    p1=ptr->right;
                    p2=ptr->right;
                    while(p1->left != NULL)
                        p1=p1->left;
                    p1->left=ptr->left;
                    free(ptr);
                    return p2;
                }
            }
        }

    }
    return(ptr);
}
/* function that search node */
struct accounts *contains(struct accounts *root)
{

    int no,i,ino,j;
    struct accounts *ptr;
    ptr=root;
    printf("\n Enter key to search:");
    scanf(" %d",&no);
    while(ptr)
    {
        if(no>ptr->key) //iterate to find key
            ptr=ptr->right;
        else if(no<ptr->key)
            ptr=ptr->left;
        else
            break; // we found it
    }
    if(ptr) // if found node is exist, print node
    {
        printf("\n Account with number %d is found",no);
        printf("\n Name: %s ",ptr->name);
        printf("\n Surname: %s ",ptr->surname);
        // this is just debug purpose
        /*for(i=0;i<ptr->numoffriends;i++){
          printf("\n Friend %d is %d",i+1,ptr->friends[i]);
        }*/
    }
    else
        printf("\n Account is not exist in the system ! ",no);
    return(root);
}
/*same function as contains, just returns 1 if found, 0 if not found  */
int searcher(struct accounts *root,int searchbyno)
{
    int no,i,ino,j;
    struct accounts *ptr;
    ptr=root;
    no=searchbyno;
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
    else
    {
        return 0;
        //printf("\n Account is not exist in the system ! ",no);}
    }
}

//using searcher function, get friends and if friends id search exists in tree(send id to searcher and check return),print it
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
        for(i=0; i<ptr->numoffriends; i++)
        {
            if(searcher(root,ptr->friends[i])==1)
            {
                //printf("\n Friend %d is %d",i+1,ptr->friends[i]);
                j++;
            }
        }
    }
    else
        printf("\n Account is not exist in the system ! ",no);
    return(root);
}
//same as contains, but it found node and behave that node as root and print inorder
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
// same as print next but it sends inorder funtion to founded nodes right node so everynode is bigger than founded node
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
