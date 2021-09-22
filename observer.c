#include <stdio.h>
#include <stdbool.h>


void loadAverages(){
   char avg[50];
   char content[50];
   char file[50];
   int i;


   sprintf(file, "/proc/loadavg");

   FILE *f = fopen(file, "r");

   fgets(content, 50, f);
   
   for(i = 0; i < 50; i++){
      if(content[i] == ' '){
         break;
      }
      avg[i] = content[i];
   }

   printf("Load Average:    %s\n", avg);
   fclose(f);

   return;
}


void getAvailableMemory(){
   char checker[13] = "MemAvailable";
   char content[250];
   char file[1000];
   int i;
   bool printThisLine = true;

   sprintf(file, "/proc/meminfo");

   FILE *f = fopen(file, "r");

   while(fgets(content, 250, f)){
      for(i=0; i < 12; i++){
         if(content[i] != checker[i]){
            printThisLine = false;
         }
      }
      if(printThisLine == true){
         printf("%s", content);
      }
      printThisLine = true;
   }
   fclose(f);

   return;
}


void getConfiguredMemory(){
   char content;
   char file[1000];

   sprintf(file, "/proc/meminfo");

   FILE *f = fopen(file, "r");

   while(content != '\n'){
      printf("%c", content);
      content = fgetc(f);
   }

   printf("\n");
   fclose(f);

   return;
}


void getProcesses(){
   char checker[10] = "processes";
   char content[250];
   char file[1000];
   int i;
   bool printThisLine = true;
   
   sprintf(file, "/proc/stat");

   FILE *f = fopen(file, "r");

   while(fgets(content, 250, f)){
      for(i = 0; i < 9; i++){
         if(content[i] != checker[i]){
            printThisLine = false;
         }
      }
      if(printThisLine == true){
         printf("%s", content);
      }
      printThisLine = true;
   }
   fclose(f);

   return;
}


void getContextSwitches(){
   char content[250];
   char file[1000];
   
   sprintf(file, "/proc/stat");

   FILE *f = fopen(file, "r");

   printf("context switches:");

   while(fgets(content, 250, f)){
      if(content[0] == 'c' && content[1] == 't'){
         int i = 4;
         while(i > 3){
            printf("%c", content[i]);
            i += 1;
            if(content[i] == '\n'){
               printf("\n");
               return;
            }
         }
      }
   }
   fclose(f);

   return;
}


void getReadWriteRequest(){
   char content[250];
   char cur[2];
   char file[1000];
   int itemNum = 0;
   char prev = ' ';
   char read[20];
   int readPoint = 0;
   char write[20];
   int writePoint = 0;

   sprintf(file, "/proc/diskstats");

   FILE *f = fopen(file, "r");
   fgets(content, 250, f);
   
   while(itemNum < 9){
      cur[0]  = (char) getc(f);
      if(prev == ' ' && cur[0] != ' '){
         itemNum += 1;
      }
      if(itemNum == 4){
         read[readPoint] = cur[0];
         readPoint += 1;
      }
      else if (itemNum == 8){
         write[writePoint] = cur[0];
         writePoint += 1;
      }
      prev = cur[0];
   }

   printf("read/write: %s/ %s\n", read, write);
   fclose(f);

   return;
}


void getCpuTime(){
   char content;
   char file[1000];
   int whiteSpaceCount = 0;

   sprintf(file, "/proc/stat");

   FILE *f = fopen(file,"r");
   content = fgetc(f);

   printf("user mode,system mode, idle times:");

   while(content != EOF){
      if(content == ' '){
         whiteSpaceCount += 1;
      }
      if(whiteSpaceCount > 1  && whiteSpaceCount < 7){
         if(whiteSpaceCount != 3){
            printf("%c", content);
         }
         if(whiteSpaceCount == 6){
            printf("\n");
            return;
         }
      }
      content = fgetc(f);

   }
   fclose(f);

   return;
}


void getHostName(){
   char content;
   char file[500];

   sprintf(file, "/proc/sys/kernel/hostname");

   FILE *f = fopen(file, "r");
   content = fgetc(f);

   printf("HostName: ");

   while(content != EOF){
      printf("%c", content);
      content = fgetc(f);
   }
   fclose(f);

   return;
}


void getDate(){
   int colonCount = 0;
   char content;
   char file[500];

   sprintf(file, "/proc/driver/rtc");

   FILE *f = fopen(file, "r");
   content = fgetc(f);
  
   printf("Date:");

   while(content != EOF){
      if(content == ':'){
         colonCount += 1;
      }
      if(colonCount == 4 && content != ':'){
         printf("%c", content);
         if(content == '\n'){
            return;
         }
      }
      content = fgetc(f);
   }
   fclose(f);

   return;
}


void getUptime(){
   int days = 0;
   char file[500];
   int hours = 0;
   float idle = 0;
   int minutes = 0;
   int seconds = 0;;
   float suspended = 0;
   int uptime = 0;
   
   sprintf(file, "/proc/uptime");

   FILE *f = fopen(file, "r");
      
   fscanf(f, "%f%f", &suspended, &idle);

   uptime = (int) (suspended + idle);

   seconds = uptime % 60;
   uptime = uptime / 60;
   minutes = uptime % 60;
   uptime = uptime / 60;
   hours = uptime % 24;
   uptime = uptime /24;
   days = uptime % 365;
   

   printf("Uptime:  %d:%d:%d:%d\n", days,hours,minutes,seconds); 
   fclose(f);

   return;
}


void getKernelVersion(){
   char file[500];
   int whiteSpaceCount = 0;

   sprintf(file, "/proc/version");

   FILE *f = fopen(file, "r");
   char content = fgetc(f);
   printf("Linux Kernel Version:");

   while(content != EOF){
      if(content == ' '){
         whiteSpaceCount += 1;
      }
      if(whiteSpaceCount == 2){
       printf("%c", content);
      }
      else if(whiteSpaceCount == 3){
         printf("\n");
         return;
      }
      content = fgetc(f);
   }
   fclose(f);

   return;
}


void getCpuName(){
   int colonCount = 0;
   char content;
   char file[1200];

   sprintf(file, "/proc/cpuinfo");

   FILE *f = fopen(file, "r");
   content = fgetc(f);
   printf("Cpu Model Name: ");

   while(content != EOF)
   {
      if(content == ':'){
         colonCount += 1;
      }
      if (colonCount == 5 && content != ':'){
         printf("%c", content);
         if(content == '\n'){
            return;
         }
      }
      content = fgetc(f);
   }
   fclose(f);

   return;
}


int main(int argc, char *argv[]){
   int duration;
   int interval;
   int iteration = 0;

   if(argc > 4){
      printf("Proper calls: observer [-s] or observer [-l interval duration]\n");
      return 0;
   }

   getCpuName();
   getKernelVersion();
   getUptime();
   getDate();
   getHostName();

   if(argc > 1){
      getCpuTime();
      getReadWriteRequest();
      getContextSwitches();
      getProcesses();
   }
   if(argc == 4){
      interval = atoi(argv[2]);
      duration = atoi(argv[3]);

      getConfiguredMemory();
      getAvailableMemory();

      while(iteration < duration){
         sleep(interval);
         loadAverages();
         iteration += interval;
      }
   }

   return 0;
}
