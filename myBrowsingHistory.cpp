#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   string sql;
   const char* data = "Callback function called";
   string  url;


	cout << "Url to search on history: ";
	getline(cin, url);
	cout << url << endl;
   /* Open database */
   rc = sqlite3_open("History.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "Select title, url, last_visit_time, visit_count from urls where url like \'%" + url + "%\'";

	int n = sql.length();
	char char_sql[n + 1];
	strcpy(char_sql, sql.c_str());
   /* Execute SQL statement */
   rc = sqlite3_exec(db, char_sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
