#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// This structure will store the details of patients required for registration.
typedef struct
{
    char emergency;
    int  department;
    char name[100];
    int  age;   
    char address[200];  
    char gender;
    char blood_grp[4];
    int aadhar_no;
    int time;
}
patient_details;

// This data type will uniquely store the ID of each patient along with department for checkup.
typedef struct 
{
    double ID;
    int dep;
} patient_ID;

// This data type will store the details of patients registered in particular department.
typedef struct 
{
    int H[100] ;
    int size ;
}dep_queue;

void swap (int *a, int *b)
{
    int temp;
    temp= *a;
    *a= *b;
    *b= temp;
}
// Below defined functions are for storing in max heap order
int parent(int i)
{
    return (i-1)/2;
}

int leftChild(int i)
{
    return 2*i +1 ;
}

int rightChild(int i)
{
    return 2*i + 2  ;
}

void shiftUp(int i, int * H)
{
    while(i>0 && H[parent(i)] < H[i])
    {
        swap(& H[parent(i)],& H[i]);
        i= parent(i);
    }
}

void shiftDown(int i, int *H , int *size)
{
    int maxIndex= i;
    int l=leftChild(i);

    if(l<= *size && H[l] > H[maxIndex])
    {
        maxIndex=l;
    }

    int r= rightChild(i);
    if(r<= * size && H[r] > H[maxIndex])
    {
        maxIndex=r;
    }
    if(i!=maxIndex)
    {
        swap(& H[i],& H[maxIndex]);
        shiftDown(maxIndex, H, size);
    }
}

void insert(int p, int *H, int * size)
{
    *size=*size+1;
    H[*size]=p;

    shiftUp(*size,H);
}
int extractMax(int *H, int * size)
{
    int result= H[0];
     H[0]=H[*size];
    *size=*size-1;
    shiftDown(0,H,size);

    return result;
} 

int main()
{

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    // Number of patients who will be registering.
    int count_patient,i;
    scanf("%d" , &count_patient);
   
    patient_details * patient_data = ( patient_details * ) malloc( count_patient * sizeof(patient_details) ) ;
    
    printf("********************************************************************************************************\n\n");
    
    for(i=0;i<count_patient;i++)
    {
        char ch, str[500];
        int temp;

        printf("Have you emergency case (Enter Y for Yes or N for NO)\n");
        scanf(" %c",&ch);
        
        patient_data[i].emergency=ch;
       
        printf("Do you know department or not:(Enter Y for Yes or N for NO)\n" );
        scanf(" %c",&ch);
     
        // If patient knows his/her department we will ask me his department number.
        // Otherwise he/she will be sent to physcian for diagnosis of the disease.

        if(ch=='Y')
        {
            printf("Enter department number \n\n");
            printf(" 0:Physician(OPD)\n 1:Gastroenterology (EMG)\n 2:Intensive Care Unit (ICU)\n 3:Neurology (NRO)\n 4:Oncology  (ONC) \n 5:ENT	(ENT) \n 6:Surgeon (SUG) \n 7:Cardiovascular (CVS)\n 8:Orthopaedic (ORP)\n 9:Pediatric (PDC)\n 10:Gynecologist(GYS) \n 11:Psychiatric(PST) \n 12:Dentistry(DNS) \n 13:Dermatology(DMT) \n 14:Radiology(RDY) \n 15:TraumaCentre (TMC)\n");
            
            scanf("%d",&temp);
            patient_data[i].department=temp;

        }
        else
        {
            printf("\nWe will send you to OPD\n");
            patient_data[i].department=0;
        }

        // Basic details have been asked for registration.

        printf("\nEnter your Name\n");
        scanf(" %s", str);
        strcpy(patient_data[i].name,str);

        printf("Enter your age \n");
        scanf(" %d", &temp);
        patient_data[i].age=temp;

        printf("Enter your address\n");
        scanf(" %s",str);
        strcpy (patient_data[i].address,str);

        printf("Enter your Gender (Enter M for MALE , F for Female, O for others)\n");
        scanf("  %c",&ch);
        patient_data[i].gender = ch;


        printf("Do you know your blood group : (Enter Y for Yes or N for NO) \n");
        scanf(" %c",&ch);

        if(ch=='Y')
        {
           printf("Enter Blood Group\n");
           scanf(" %s",str);
           strcpy( patient_data[i].blood_grp,str);
        }
        else
        {
            strcpy(patient_data[i].blood_grp ,"NA") ;
        }
         
        printf("Enter your AADHAR NO.\n");
        scanf(" %d",&temp);
        patient_data[i].aadhar_no=temp;

        printf("Enter TIME \n\n");
        scanf(" %d",&temp);
        patient_data[i].time=temp;

        printf("********************************************************************************************************\n\n");
    }

    /*for(i=0;i<count_patient;i++)
    {
        printf("Patient No. %d \n", 1+i);

        printf("%s",patient_data[i].name);
        printf("\n");

        printf( "%d",patient_data[i].age);
        printf("\n");

        printf("%d", patient_data[i].department);
        printf("\n");
        
        printf( "%d",patient_data[i].aadhar_no);
        printf("\n");

        printf( "%s",patient_data[i].address);
        printf("\n");

        printf("%c",patient_data[i].gender);
        printf("\n");

        printf("\n");
        printf("********************************************************************************************************\n\n");
    }*/

////  UNIQUE ID GENERATION of each patient.
//// Max heap concept is used here to decide priority.

    patient_ID* PAT_ID = (patient_ID* )malloc(count_patient* sizeof(patient_ID )) ;
  
    for(i=0;i<count_patient;i++)
    {
        if(patient_data[i].emergency=='Y')
            PAT_ID[i].ID=1;
        else
            PAT_ID[i].ID=0;

        // To give less priority to late registrations time is being subtracted from 2400 (2400 is maximum time possible in 24 hour time format)
         
         patient_data[i].time= 2400- patient_data[i].time;

         // i is added to patient ID because it will later help in extracting the required patient information.
         patient_data[i].time= patient_data[i].time * 1e4+ i;

         PAT_ID[i].ID =  PAT_ID[i].ID * 1e8 + patient_data[i].time; 
         PAT_ID[i].dep = patient_data[i].department;
        
    }

    dep_queue* DEP_Q = (dep_queue*) malloc (17* sizeof (dep_queue) ) ;

    //Initialise size to -1 of each priority queue

    for(i=0;i<16;i++)
    DEP_Q[i].size=-1;

    for(i=0;i<count_patient;i++)
    {
        int cur_dep= PAT_ID[i].dep;
        insert (PAT_ID[i].ID, DEP_Q[cur_dep].H,  & DEP_Q[cur_dep].size);
    }

    for(i=0;i<17;i++)
    {
        printf("For the Department of ");
        switch(i)
        {
                case 0: printf("Physician(OPD)\n");
                        break;
                case 1: printf("Gastroenterology\n");
                         break;
                case 2: printf("Intensive Care Unit (ICU)\n");
                        break;
                case 3: printf("Neurology (NRO)\n");
                         break;
                case 4: printf("Oncology (ONC)\n");
                         break;
                case 5: printf("ENT(ENT)\n");
                         break;
                case 6: printf("Surgeon (SUG)\n");
                        break;
                case 7: printf("Cardiovascular (CVS)\n");
                        break;
                case 8: printf("Orthopaedic (ORP)\n");
                         break;
                case 9: printf("Pediatric (PDC)\n");
                        break;
                case 10: printf("Gynecologist(GYS)\n");
                        break;
                case 11: printf("Psychiatric(PST)\n");
                        break;
                case 12: printf("Dentistry(DNS)\n");
                        break;
                case 13: printf("Dermatology(DMT)\n");
                        break;
                case 14: printf("Radiology(RDY)\n");
                        break;
                case 15: printf("TraumaCentre (TMC)\n");
                        break;
        }

        if(DEP_Q[i].size ==-1)
        printf("No patient visited\n\n");
        else
        {
            printf("The list of patients in sequential manner is as follows\n\n");

            while( DEP_Q[i].size >=0 )
            {

                int u=extractMax(DEP_Q[i].H, & DEP_Q[i].size);

              //  printf("%d %d \n",u,u- 10000* (u/10000) );
                int d=u- 10000* (u/10000);

                printf("Patient name = %s\n",patient_data[d].name);
                printf("Patient ID = %d \n\n", u);

            }
         
        }
        printf("********************************************************************************************************\n\n");
    }
    return 0;
}
  