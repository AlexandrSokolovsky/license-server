#include <iostream>
#include <string>
#include <chrono>
#include <math.h>
#include <vector>
#include <random>
#include <algorithm>
#include <boost/functional/hash/hash.hpp>

#include <ctime>
#include <sys/wait.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>


#include <pqxx/pqxx> 

//g++ -o ./pgsqltest ./pgsqltest02.cpp -I /opt/libpqxx/include -L /opt/libpqxx/lib -lpq -lpqxx
//./pgsqltest

using namespace std;
using namespace pqxx;
using namespace std::chrono;


long long *v = new long long[3];

struct user_data
{
   string MAC = " \'";
   string CPU_NAME = " \'";
   string CPU_MNFC = " \'";
   string BOARD_CHPS = " \'";
   string BOARD_ID = " \'";
   string RAM_CPCTY = " \'";
   string RAM_CLK = " \'";
   string GPU_NAME = " \'";
   string GPU_RAM = " \'";
   string OS_SERIAL = " \'";
   string TIME_REMAIN = " \'";
   string TIME_DAYS = "3";
   string test_FPS = " \'";

/*
XQ,DATA_F,MAC,CPU_NAME,CPU_MNFC,
BOARD_CHPS,BOARD_ID,RAM_CPCTY,RAM_CLK,
GPU_NAME,GPU_RAM,OS_SERIAL,OS_SERIAL,
TIME_DAYS,DATE_START,FPS*/

};

string generate_pass();
user_data collect_usr_data(int sock);
string random_string();
bool check_data();

int main(int argc, char* argv[])
{
   string sql;

   int sock, listener;
   struct sockaddr_in addr;
   char buf_key[100];
   char buf_data[100];
   char buff[] = "kek";
   char buf1[] = "kkk";
   char buffps[] = "fps";
   char buf_ext[] = "ext";
   char buf_ok[] = "aok";
   int bytes_read;
   string get_data = "";

   listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }

   try {
      connection C("dbname = postgres user = postgres password =  rrHQrWwU9k \
      hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) 
      {
            cout << "Opened database successfully: " << C.dbname() << endl;
         } else {
            cout << "Can't open database" << endl;
            return 1;
         }



/*
 sql = "CREATE TABLE COMPANY("  \
      "KEY TEXT PRIMARY KEY  NOT NULL," \
      "XQ               BOOL NOT NULL," \
      "DATA_F           BOOL NOT NULL," \
      "MAC              TEXT," \
      "CPU_NAME         TEXT," \
      "CPU_MNFC         TEXT," \
      "BOARD_CHPS       TEXT," \
      "BOARD_ID         TEXT," \
      "RAM_CPCTY        TEXT," \
      "RAM_CLK          TEXT," \
      "GPU_NAME         TEXT," \
      "GPU_RAM          TEXT," \
      "OS_SERIAL        TEXT," \
      "TIME_REMAIN      INT," \
      "TIME_DAYS        INT," \
      "DATE_START       date," \
      "FPS              real);";

      // Create a transactional object. 
      work W0(C);
      
      // Execute SQL query 
      W0.exec( sql );
      W0.commit();
      cout << "Table created successfully" << endl;
*/
C.disconnect ();
 long long t = time_point_cast<nanoseconds>(system_clock::now()).time_since_epoch().count();
 user_data INFO;


//for(int i =0; i < 500; i ++)      //поставить здесь форк
int kk=0;

addr.sin_family = AF_INET;
    addr.sin_port = htons(10050);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }


string test_KEY = "";
pid_t c_pid = fork();

if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (c_pid > 0) {
          
        wait(nullptr);
    } else {
      close(listener);
      send(sock, buf1, sizeof(buf1), 0);
      bytes_read = recv(sock, buf_key, sizeof(buf_key), 0);
      
                if(bytes_read <= 0) break;
                //send(sock, buf, bytes_read, 0);
		//write(1, &buf, bytes_read);

        connection C("dbname = postgres user = postgres password =  rrHQrWwU9k \
      hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) 
      {
         
         work W(C);
         pqxx::result rt{W.exec("SELECT * FROM company WHERE time_remain <= 0")};
         if (rt.size() > 0)
            cout<<"rt="<<rt.size()<<endl;
         sql = "DELETE from COMPANY where time_remain <= 0";

         /* Execute SQL query */
         
         W.exec( sql );
       //  W.commit();
        string get_key;
                 cout<<"bytes_read="<<bytes_read<<endl;
         for(int y = 0; y < bytes_read - 1; y ++)
         {            
            if(buf_key[y] == ' ')
               break;
            get_key += buf_key[y];  //получаю от юзера
         }
            bytes_read = 0;
            cout<<"buf="<<buf_key<<endl;
        //work Wr(C);
        pqxx::result gk{W.exec("SELECT * FROM company WHERE key = \'"+get_key+"\'")};
        cout<<"gk:"<<gk.size()<<endl;
        if(gk.size() > 0)
        {
                pqxx::result gk1{W.exec("SELECT * FROM company WHERE key = \'"+get_key+"\' AND DATA_F = FALSE")};
                  cout<<"gk1:"<<gk1.size()<<endl;
                  if(gk1.size() > 0)
                  {
                  if(INFO.TIME_REMAIN > INFO.TIME_DAYS)
                     {
                        INFO.TIME_REMAIN = INFO.TIME_DAYS;
                     }
                  sql = "UPDATE COMPANY SET (TIME_REMAIN, DATE_START) = (TIME_REMAIN-(CURRENT_DATE - DATE_START), CURRENT_DATE)"
                        "WHERE key = \'"+get_key+"\';";
                  
//tyt

                  INFO = collect_usr_data(sock); //получаю от юзера
                  cout<<"fff = "<<INFO.test_FPS<<endl;
                  cout<<"INFO.BOARD_CHPS = "<<INFO.BOARD_CHPS<<endl;
                  sql = "UPDATE COMPANY SET (XQ,DATA_F,MAC,CPU_NAME,CPU_MNFC,BOARD_CHPS,BOARD_ID,RAM_CPCTY, RAM_CLK,GPU_NAME,GPU_RAM,OS_SERIAL,DATE_START,FPS) = (TRUE, TRUE," + INFO.MAC + ", " + INFO.CPU_NAME + ", "+ INFO.CPU_MNFC +", "+ INFO.BOARD_CHPS +", "+ INFO.BOARD_ID + ", "+ INFO.RAM_CPCTY +","+ INFO.RAM_CLK +", "+ INFO.GPU_NAME + ", "+ INFO.GPU_RAM + ", "+ INFO.OS_SERIAL +", CURRENT_DATE, " +INFO.test_FPS+")"
                        "WHERE key = \'"+get_key+"\';";
                  cout<<"buff="<<buf1<<endl;
                  send(sock, buf_ok, sizeof(buf_ok), 0);
                  }else
                  {                     
                     //send(sock, buf1, sizeof(buf1), 0);
                     INFO = collect_usr_data(sock);

                     pqxx::result gk{W.exec("SELECT * FROM company WHERE " \
                     "key = \'"+get_key+"\' AND " \
                     "XQ = TRUE AND " \
                     "DATA_F = TRUE AND " \
                     "MAC        = "+INFO.MAC+" AND  " \
                     "CPU_NAME    = "+INFO.CPU_NAME+" AND " \
                     "CPU_MNFC    = "+INFO.CPU_MNFC+" AND "\
                     "BOARD_CHPS     = "+INFO.BOARD_CHPS+" AND " \
                     "BOARD_ID        ="+INFO.BOARD_ID+" AND " \
                     "RAM_CPCTY       = "+INFO.RAM_CPCTY+" AND " \
                     "RAM_CLK         = "+INFO.RAM_CLK+" AND " \
                     "GPU_NAME        = "+INFO.GPU_NAME+" AND " \
                     "GPU_RAM         = "+INFO.GPU_RAM+" AND "\
                     "OS_SERIAL        = "+INFO.OS_SERIAL)};

                     cout<<"gk size:"<<gk.size()<<endl;
                     if(gk.size() > 0)
                     {
                        if(INFO.TIME_REMAIN > INFO.TIME_DAYS)
                        {
                           INFO.TIME_REMAIN = INFO.TIME_DAYS;
                        }
                        sql = "UPDATE COMPANY SET (TIME_REMAIN, DATE_START,FPS) = (TIME_REMAIN-(CURRENT_DATE - DATE_START), CURRENT_DATE,"+INFO.test_FPS+")"
                              "WHERE key = \'"+get_key+"\';";
                              send(sock, buf_ok, sizeof(buf_ok), 0);
                     }else{
                        send(sock, buf_ext, sizeof(buf_ext), 0);
                        cout<<"fuck u"<<endl;
                     }
                  }

        }   
        else
        {
           
         pqxx::result r;
         int rs = 0;
            do{
               try {
               test_KEY = random_string();
               r.clear();
               r = W.exec("SELECT * FROM company WHERE key = \'"+test_KEY+"\'");
               rs = r.size();
           //    W.commit();
           //    cout<<"xqz"<<endl;
               }catch (const exception& e) {
                  cout<<e.what();    
                throw;
                  }
            }while(rs > 0);
   //string test_KEY = generate_pass() + "\'";
   /* Create SQL statement */
         sql = "INSERT INTO COMPANY (KEY,XQ,DATA_F) "  \
            "VALUES (\'" + test_KEY + "\', FALSE, FALSE); ";
         send(sock, buf_ext, sizeof(buf_ext), 0);
        }
//Wr.commit();
         /* Create a transactional object. */
        // work W1(C);
         
        // cout<<"qwe"<<endl;
         /* Execute SQL query */
        // cout<<"sql = "<<sql<<endl;
         W.exec( sql );
         W.commit();
         
            _exit(0);
      close(sock);
      C.disconnect ();   
      } else {
         return 1;
      }



        exit(EXIT_SUCCESS);
    }
}
t = time_point_cast<nanoseconds>(system_clock::now()).time_since_epoch().count() - t;
cout<<"time = "<<t/(pow(10,9))<<endl;
      close(listener);
   } catch (sql_error const &e) {
      cerr <<e.what() << std::endl;
      cerr << "Query was: " << e.query() << std::endl;
      return 1;
   }

   return 0;
}



string random_string()
{
     string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

     random_device rd;
     mt19937 generator(rd());

     std::shuffle(str.begin(), str.end(), generator);

     return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

user_data collect_usr_data(int sock)
{
     random_device rd;
     mt19937 generator(rd());
   int bytes_read = 0;
   char buf1[] = "kek";
   char buffps[] = "fps";
   char buf_fps[20];
   char buf_data[300];
   vector<string> get_data;
   string gd;
   string fps_d;

   send(sock, buf1, sizeof(buf1), 0);
                  while(bytes_read == 0)
                  {
                     bytes_read = recv(sock, buf_data, sizeof(buf_data), 0);
                  }
                  cout<<"buf_data:"<<buf_data<<" bread:"<<bytes_read<<endl;
                  for(int y = 0; y < bytes_read - 1; y ++)
                  { 
                     if(buf_data[y] == '\'')
                     { 
                        get_data.push_back(gd);
                        gd.clear();
                        y++;

                        if( (buf_data[y] == '\'') && (buf_data[y-1] == '\'') )
                        {
                           gd = "NONE";
                           get_data.push_back(gd);
                           gd.clear();
                           y++;
                        }
                     }
                     gd += buf_data[y];  //получаю от юзера
                  }
                  cout<<"gd = "<<gd<<endl;
   bytes_read = 0;
   send(sock, buffps, sizeof(buffps), 0);
    while(bytes_read == 0)
                  {
                     bytes_read = recv(sock, buf_fps, sizeof(buf_fps), 0);
                  }
                  cout<<"buf_fps:"<<buf_fps<<" bread:"<<bytes_read<<endl;
                  for(int y = 0; y < bytes_read - 2; y ++)
                  { 
                     fps_d += buf_fps[y];  //получаю от юзера
                     if(buf_fps[y+1] == '\'')
                        break;
                  }
                  cout<<"fps_d = "<<fps_d<<endl;

   user_data temp_INFO{get_data[0],get_data[1],get_data[2],
   get_data[3],get_data[4],get_data[5],get_data[6],
   get_data[7],get_data[8],get_data[9],"1","1",fps_d};
   hash<string> hash1;


/*
   string MAC;          0
   string CPU_NAME;     1
   string CPU_MNFC;     2
   string BOARD_CHPS;   3
   string BOARD_ID;     4
   string RAM_CPCTY;    5
   string RAM_CLK;      6
   string GPU_NAME;     7
   string GPU_RAM;      8
   string OS_SERIAL;    9
*/

   temp_INFO.MAC = "\'" + temp_INFO.MAC +  "\'";
   temp_INFO.CPU_NAME = "\'" + temp_INFO.CPU_NAME +  "\'";
   temp_INFO.CPU_MNFC = "\'" + temp_INFO.CPU_MNFC +  "\'";
   temp_INFO.BOARD_CHPS = "\'" + temp_INFO.BOARD_CHPS +  "\'";
   temp_INFO.BOARD_ID = "\'" +temp_INFO.BOARD_ID+  "\'" ;
   temp_INFO.RAM_CPCTY = "\'" + temp_INFO.RAM_CPCTY +  "\'";
   temp_INFO.RAM_CLK = "\'" + temp_INFO.RAM_CLK +  "\'";
   temp_INFO.GPU_NAME = "\'" + temp_INFO.GPU_NAME +  "\'";
   temp_INFO.GPU_RAM = "\'" + temp_INFO.GPU_RAM +  "\'";
   temp_INFO.OS_SERIAL = "\'" + temp_INFO.OS_SERIAL  +  "\'";

   temp_INFO.TIME_DAYS = "\'" + temp_INFO.TIME_DAYS +  "\'";      //get from http server with msg with licens   
   return temp_INFO;
}

string generate_pass()
{
   string temp;
   string str = "\'";
   string st = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm";
   for(int i = 0; i < 10; i++)
   {      
      long long t = time_point_cast<nanoseconds>(system_clock::now()).time_since_epoch().count();
      int k = 0;
      for(int i = 0 ; i < 1000; i++)
      {
         int k = 0;
         k++;
      }
      t = time_point_cast<nanoseconds>(system_clock::now()).time_since_epoch().count() - t;
      temp = to_string(t);
      if(temp.size() - 3 > 0)
      {
         t = int(t / pow(10,temp.size() - 3));
      }
      if(temp.size() - 3 < 0)
      {
         t = t * pow(10,temp.size() -3);
      }
      v[i] = t;
      str = str + to_string(t);
  
      while(t > 52)
         t = int(t/53);
   for(int i = 0; i < str.size(); i++)
   {
      if (str[i] == '0')  
      {
         str[i] = st[rand()%t];
      }
   }
   }

   cout<<"str = "<<str<<endl;
   return str;
}