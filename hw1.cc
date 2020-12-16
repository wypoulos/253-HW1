#include <iostream>
#include <vector>
#include <time.h> 

using namespace std;

string dayFmtAj(int day);
string yearFmtAj(int year);
bool isValidForm(string str);
vector<string> dataIn();
bool isLepYr(int year);
int getMnthNum(int day, bool leap);
int getDayofWeek(int yr, int day);
string mthToName(int month);
string dayToName(int day);
int doM(int doY, int year);

string prgmName;

int main(int, char *argv[]) {
	prgmName = argv[0];
	vector<string> values (dataIn());

	for(int i = 0; i < int(values.size()); i++){
		if(!(isValidForm(values[i]))){
			cerr << prgmName << " Error: " << "Invalid Formating" << "\n";
                        exit (1);
		}
		string str = values[i];
		int index = str.find('.');
		string yr, dy;
		int year, day;
		dy = str.substr(index + 1);
		yr = str.substr(0, index);
		try{
			day = stoi(dy);
			year = stoi(yr);
		}catch(const std::exception& e){
			cerr << prgmName << " Error: Invalid Formating \n";
			exit(1);
		}
		if(year > 9999 || year < 1){
			cerr << prgmName << " Error: " << "Year out of range" << "\n";
			exit (1);
		}
		yr = yearFmtAj(year);
		dy = dayFmtAj(doM(day, year));
		cout << dayToName(getDayofWeek(year, day)) << " " << dy << " ";
		cout << mthToName(getMnthNum(day, isLepYr(year))) << " " << yr << "\n";
	}
	return 0;
}
string dayFmtAj(int day){
	string dayFt = to_string(day);
	if(dayFt.size() == 2){return dayFt;}
	return '0' + dayFt;
}
string yearFmtAj(int year){
	string yearFt = to_string(year);
	string zeros[] = {"0","00","000"};
	if(yearFt.size() == 4){return yearFt;}
	return zeros[3-yearFt.size()] + yearFt;
}
bool isValidForm(string str){
	int dotCnt = 0;
	size_t search = str.find('.');
	if(search == string::npos){return false;}
	for(int i = 0; i < int(str.length()); i++){
		char s = str[i];
		if(!((s >= '0' && s <= '9') || s == '.')){
			return false;
		}
		if(s == '.'){
			dotCnt++;
		}
	}
	if(dotCnt > 1){
		return false;
	}
	return true;
}

vector<string> dataIn(){
	string sline;
	vector<string> data;
	while(cin >> sline){
		data.push_back(sline);
	}
	if(data.empty()){
		cerr << prgmName << " Error: " << "No Values Found" << "\n";
		exit (1);
	}
	return data;
}

bool isLepYr(int year){
	if(year%4 == 0){
		if(year%100 == 0){
			if(year%400 == 0){
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

int getMnthNum(int day, bool leap){
	int a = 0;
	if(leap){
		a = 1;	
	}
	if(day > 0 && day <= 31){
		return 1;	
	}
	if(day >= 32 && day <= 59 + a){
		return 2;
	}
	if(day >= 60 + a && day <= 90 + a){
		return 3;
	}
	if(day >= 91 + a && day <= 120 + a){
		return 4;
	}
	if(day >= 121 + a && day <= 151 + a){
		return 5;
	}
	if(day >= 152 + a && day <= 181 + a){
		return 6;
	}
	if(day >= 182 + a && day <= 212 + a){
		return 7; 
	}
	if(day >= 213 + a && day <= 243 + a){
		return 8;
	}
	if(day >= 244 + a && day <= 273 + a){
		return 9;
	}
	if(day >= 274 + a && day <= 304 + a){
		return 10;
	}
	if(day >= 305 + a && day <= 334 + a){
		return 11;
	}
	if(day >= 335 + a && day <= 365 + a){
		return 12;
	}
	return 0;
}

int getDayofWeek(int yr, int day){
	struct tm timeinfo = {};
	timeinfo.tm_year = yr - 1900;
	timeinfo.tm_mday = day;
	
	mktime(&timeinfo); 	
	return timeinfo.tm_wday;
}

string mthToName(int month){
	string months[] ={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	return months[month - 1];
}

string dayToName(int day){
	string wdys[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	return wdys[day];
}

int doM(int doY, int year){
	int e = 0;
	if(isLepYr(year)){e = 1;}
	if(doY < 1 || doY > 365 + e){
		cerr << prgmName << " Error: " << "Day out of range" << "\n";
		exit (1);
	}

	struct tm timeinfo = {};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mday = doY;

        mktime(&timeinfo);
        return timeinfo.tm_mday;
}


