#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<queue>
using namespace std;

//病人
class Patient
{
public:
	Patient(string na, string nu, string inu,string rnu) :name(na), number(nu), identification_number(inu),register_number(rnu) {}
	string get_name() { return name; }
	string get_number() { return number; }
	string get_identification_number() { return identification_number; }
	string get_register_number() { return register_number; }
private:
	string name;//
	string number;//
	string identification_number;//
	string register_number;//

};

class Doctor
{
public:
	Doctor(string,string);//
	string get_doctor_department_name();//
	string get_doctor_name();//
	int get_max_number();//
	int get_present_number();//
	void set_present_number(int);//
	void register_patients(Patient*);//
private:
	string doctor_department_name;//
	string doctor_name;//
	const int max_number = 100;//
	int present_number;//
	queue<Patient*> patients;//
};

class Department
{
public:
	Department(string);//
	string get_department_name();
	int get_doctor_number();
	string* get_doctor_name();
	Doctor* get_doctor(int);
	Doctor** get_doctors();
private:
	string department_neme;
	Doctor** doctors;
	int doctor_number;
};

class Hospital
{
public:
	Hospital();
	string* get_department_name();
	int get_department_number();
	int get_doctor_number();
	Department* get_department(int);
	int register_by_doctor(string);
	int register_by_department(int);
private:
	Department** departments;
	string* department_name;
	Patient** patients;
	int department_number;
	int doctor_number;
	int patient_number;
};

int main(void)
{
	system("title \"药到命除\"挂号系统");
	Hospital hospital;
	int choose = 0;
	string doctor;
	int n = 1;
	while (true)
	{
		int index = 1;
		string* department_name;
		system("cls");
		switch (n)
		{
		case 1:
			cout << "欢迎使用\"药到命除\"挂号系统" << endl;
			cout << "----------------------------------" << endl;
			cout << 0 << left << setw(13) << ".退出" << 1 << left << setw(13) << ".挂号" << endl;
			cout << "请选择：";
			cin >> choose;
			if (choose == 0)exit(1);
			if (choose == 1) { system("cls"); n++; }
			continue;
		case 2:
			cout << "请选择挂号方式" << endl;
			cout << "----------------------------------" << endl;
			cout << 0 << left << setw(13) << ".退出" << endl;
			cout << 1 << left << setw(13) << ".按科室挂号"<< "     " << 2 << ".按医生挂号" << endl;
			cout << -1 << ".返回" << endl;
			cout << "请选择：";
			cin >> choose;
			if (choose == 0)exit(1);
			else if (choose == -1) { system("cls"); n--; }
			else { system("cls"); n++; }
			continue;
		case 3:
			if (choose == 1) {
				cout << "按科室挂号" << endl;
				cout << "----------------------------------" << endl;
				cout << " " << 0 << ".退出" << endl;
				department_name = hospital.get_department_name();
				for (int i = 0; i < hospital.get_department_number(); i++) {
					if (index < 10)cout << " ";
					cout << index << "." << left << setw(13) << department_name[i];
					index++;
					if ((index - 1) % 2 == 0)cout << endl;
				}
				cout << -1 << ".返回" << endl;
				cout << "请选择科室：";
				cin >> choose;
				n += hospital.register_by_department(choose);
				choose = 1;
				if (n == 4) {
					cout << "----------------------------------" << endl;
					cout << 0 << ".退出" << "    " << 1 << ".继续挂号" << endl;
					cout << "请选择：";
					cin >> choose;
					if (choose == 0)exit(1);
					else if (choose == 1) { system("cls"); n = 1; }
					else return 0;
				}
				continue;
			}
			else if (choose == 2) {
				cout << "按医生挂号" << endl;
				cout << "----------------------------------" << endl;
				cout << " " << 0 << ".退出" << endl;
				cout << -1 << ".返回" << endl;
				cout << "请输入医生姓名：";
				cin >> doctor;
				n += hospital.register_by_doctor(doctor);
				if (n == 4) {
					cout << "----------------------------------" << endl;
					cout << 0 << ".退出" << "    " << 1 << ".继续挂号" << endl;
					cout << "请选择：";
					cin >> choose;
					if (choose == 0)exit(1);
					else if (choose == 1) { system("cls"); n = 1; }
					else return 0;
				}
				continue;
			}
			break;
		default:
			break;
		}
		cin >> choose;
	}
	return 0;
}

//Class_Doctor_Mathod
Doctor::Doctor(string dapartment_name,string doctor_name)
{
	doctor_department_name = dapartment_name;
	this->doctor_name = doctor_name;
	present_number = 0;
}

string Doctor::get_doctor_department_name()
{
	return doctor_department_name;
}

string Doctor::get_doctor_name()
{
	return doctor_name;
}

int Doctor::get_max_number()
{
	return max_number;
}

int Doctor::get_present_number()
{
	return present_number;
}

void Doctor::set_present_number(int i)
{
	present_number+=i;
}

void Doctor::register_patients(Patient* patient)
{
	patients.push(patient);
	set_present_number(1);
}

//Class_Department_Mathod
Department::Department(string department_name)
{
	//cout << setw(13) << "Department";
	this->department_neme = department_name;
	doctor_number = 0;
	ifstream infile;
	infile.open("Hospital\\" + department_name + ".txt", ios::in);
	string doctor_name;
	while (infile>>doctor_name)
	{
		doctor_number++;
		if (doctor_number > 1) {
			Doctor** old_doctors = doctors;
			doctors = new Doctor*[doctor_number];
			for (int i = 0; i < doctor_number-1; i++)
			{
				doctors[i] = old_doctors[i];
			}
		}
		else
		{
			doctors = new Doctor*[doctor_number];
		}
		doctors[doctor_number - 1] = new Doctor(department_name, doctor_name);
	}
}

string Department::get_department_name()
{
	return department_neme;
}

int Department::get_doctor_number()
{
	return doctor_number;
}

string* Department::get_doctor_name()
{
	string* doctor_name = new string[doctor_number];
	for (int i = 0; i < doctor_number; i++) {
		doctor_name[i]=doctors[i]->get_doctor_name();
	}
	return doctor_name;
}

Doctor* Department::get_doctor(int i)
{
	return doctors[i];
}

Doctor** Department::get_doctors()
{
	return doctors;
}

//Class_Hospital_Mathod
Hospital::Hospital()
{
	//cout << setw(13) << "Hospital";
	department_number = 0;
	doctor_number = 0;
	patient_number = 0;
	department_name = NULL;
	departments = NULL;
	ifstream infile_Hospital("Hospital\\Department.txt", ios::in);
	string department_name_medium;
	while (infile_Hospital >> department_name_medium) {
		department_number++;
		//departments
		if (department_number > 1) {
			Department** old_departments = departments;
			departments = new Department * [department_number];
			for (int i = 0; i < department_number-1; i++)
			{
				departments[i] = old_departments[i];
			}
		}
		else
		{
			departments = new Department * [department_number];

		}
		departments[department_number - 1] = new Department(department_name_medium);
		//department_name
		if (department_number > 1) {
			string* old_department_name = department_name;
			department_name = new string[department_number];
			for (int i = 0; i < department_number - 1; i++)
			{
				department_name[i] = old_department_name[i];
			}
		}
		else
		{
			department_name = new string[department_number];

		}
		department_name[department_number - 1] = department_name_medium;
		doctor_number += departments[department_number - 1]->get_doctor_number();
	}
	ifstream infile_patient("Hospital\\Patient.txt", ios::in);
	string na;
	string nu;
	string inu;
	string rnu;
	while (infile_patient>>na>>nu>>inu>>rnu)
	{
		patient_number++;
		if (patient_number > 1) {
			Patient** old_patients = patients;
			patients = new Patient * [patient_number];
			for (int i = 0; i < patient_number - 1; i++)
			{
				patients[i] = old_patients[i];
			}
		}
		else
		{
			patients = new Patient * [patient_number];
		}
		patients[patient_number - 1] = new Patient(na,nu,inu,rnu);
		char* char_rnu=new char();
		strcpy(char_rnu, rnu.c_str());
		char** number = new char*[3];
		number[0] = strtok(char_rnu, "-");
		number[1] = strtok(NULL, "-");
		number[2] = strtok(NULL, "-");
		int i = 0, j = 0;
		for (int z = 0; z < strlen(number[0]); z++) {
			i = i * 10 + int(number[0][z] - '0');
		}
		for (int z = 0; z < strlen(number[1]); z++) {
			j = j * 10 + int(number[1][z] - '0');
		}
		Department* department = departments[i-1];
		Doctor* doctor = department->get_doctor(j-1);
		doctor->register_patients(patients[patient_number - 1]);
	}
}

string* Hospital::get_department_name()
{
	return department_name;
}

int Hospital::get_department_number()
{
	return department_number;
}

int Hospital::get_doctor_number()
{
	return doctor_number;
}

Department* Hospital::get_department(int i)
{
	return departments[i];
}

int Hospital::register_by_doctor(string doctor_)
{
	int register_department_number = 0;
	int register_doctor_number = 0;
	if (doctor_ == "0")exit(1);
	if (doctor_ == "-1") {system("cls"); return -1; }
	int index = 0;
	for (int i = 0; i < get_department_number(); i++)
	{
		Department* department = departments[i];
		Doctor** department_doctor = department->get_doctors();
		for (int j = 0; j < department->get_doctor_number(); j++)
		{
			if (department_doctor[j]->get_doctor_name() == doctor_)index++;
		}
	}
	Doctor** choose_doctor = new Doctor * [index];
	index = 0;
	cout << "----------------------------------" << endl;
	for (int i = 0; i < get_department_number(); i++)
	{
		Department* department = departments[i];
		Doctor** department_doctor = department->get_doctors();
		for (int j = 0; j < department->get_doctor_number(); j++)
		{
			if (department_doctor[j]->get_doctor_name() == doctor_) {
				cout << (index + 1) << "." << department_doctor[j]->get_doctor_department_name() << ": ";
				cout << department_doctor[j]->get_doctor_name() << endl;
				cout << "  已挂号人数:" << department_doctor[j]->get_present_number() << "\t";
				cout << "余号:" << department_doctor[j]->get_max_number() - department_doctor[j]->get_present_number() << endl;
				choose_doctor[index++] = department_doctor[j];
			}
		}
	}
	cout << "请选择:";
	int choose;
	while (cin>>choose)
	{
		if (choose == 0)exit(1);
		if (choose == -1) { system("cls"); return 0; }
		if (choose <= index)break;
		cout << "请重新选择:";
	}
	for (int i = 0; i < department_number; i++)
	{
		if (departments[i]->get_department_name() == choose_doctor[choose - 1]->get_doctor_department_name()) {
			Department* department = departments[i];
			register_department_number = i + 1;
			for (int j = 0; j < department->get_doctor_number(); j++)
			{
				Doctor* doctor = department->get_doctor(j);
				if (doctor->get_doctor_name() == choose_doctor[choose - 1]->get_doctor_name())
				{
					register_doctor_number = j + 1;
					break;
				}
			}
			break;
		}
	}
	system("cls");
	cout << "您选择了:" << choose_doctor[choose - 1]->get_doctor_name() << "医生" << endl;
	cout << "----------------------------------" << endl;
	Doctor* doctor = choose_doctor[choose - 1];
	cout << "确定挂号吗？" << endl;
	cout << 1 << ".确定" << endl;
	cout << 0 << ".退出" << "   " << -1 << ".返回" << endl;
	cout << "请选择：";
	cin >> choose;
	if (choose == 0)exit(1);
	if (choose == -1) { system("cls"); return -1; }
	if (choose == 1) {
		system("cls");
		string name;
		string number;
		string idantification_number;
		cout << "----------------------------------" << endl;
		cout << "请输入您的姓名：";
		cin >> name;
		cout << "请输入电话号码：";
		cin >> number;
		cout << "请输入身份证号：";
		cin >> idantification_number;
		string register_number = to_string(register_department_number) + "-" + to_string(register_doctor_number) + "-" + to_string(doctor->get_present_number());
		Patient* patient = new Patient(name, number, idantification_number, register_number);
		doctor->register_patients(patient);
		system("cls");
		cout << "挂号成功！挂号信息如下:" << endl;
		cout << "----------------------------------" << endl;
		cout << "    姓名：" << patient->get_name() << endl;
		cout << "电话号码：" << patient->get_number() << endl;
		cout << "身份证号：" << patient->get_identification_number() << endl;
		cout << "    序号：" << patient->get_register_number() << endl;
		cout << "----------------------------------" << endl;
		ofstream outfile("Hospital\\Patient.txt", ios::app);
		outfile << patient->get_name() << " "
			<< patient->get_number() << " "
			<< patient->get_identification_number() << " "
			<< patient->get_register_number() << " ";
		outfile.close();
	}
	return 1;
}

int Hospital::register_by_department(int choose)
{
	int register_department_number, register_doctor_number;
	system("cls");
	if (choose == 0)exit(1);
	if (choose == -1) return -1;
	if (choose > department_number)return 0;
	register_department_number = choose;
	cout << -1 << ".返回" << "   " << 0 << ".退出" << endl;
	cout << "----------------------------------" << endl;
	cout << "您选择了:" << departments[choose-1]->get_department_name() << endl;
	cout << "医生有：" << endl;
	Doctor** choose_doctor = departments[choose-1]->get_doctors();
	for (int i = 0; i < departments[choose-1]->get_doctor_number(); i++)
	{
		cout << (i + 1) << "." << choose_doctor[i]->get_doctor_name() << endl;
		cout << "  已挂号人数:" << choose_doctor[i]->get_present_number() << "\t";
		cout << "余号:" << choose_doctor[i]->get_max_number() - choose_doctor[i]->get_present_number() << endl;
	}
	cout << "请选择:";
	while (cin >> choose)
	{
		if (choose == 0)exit(1);
		if (choose == -1) { system("cls"); return 0; }
		if (choose <= departments[choose - 1]->get_doctor_number())break;
		cout << "请重新选择:";
	}
	register_doctor_number = choose;
	system("cls");
	cout << "您选择了:" << choose_doctor[choose - 1]->get_doctor_name() << "医生" << endl;
	cout << "----------------------------------" << endl;
	Doctor* doctor = choose_doctor[choose - 1];
	cout << "确定挂号吗？" << endl;
	cout << 1 << ".确定" << endl;
	cout << 0 << ".退出" << "   " << -1 << ".返回" << endl;
	cout << "请选择：";
	cin >> choose;
	if (choose == 0)exit(1);
	if (choose == -1) { system("cls"); return -1; }
	if (choose == 1) {
		system("cls");
		string name;
		string number;
		string idantification_number;
		cout << "----------------------------------" << endl;
		cout << "请输入您的姓名：";
		cin >> name;
		cout << "请输入电话号码：";
		cin >> number;
		cout << "请输入身份证号：";
		cin >> idantification_number;
		string register_number = to_string(register_department_number) + "-" + to_string(register_doctor_number) + "-" + to_string(doctor->get_present_number());
		Patient* patient = new Patient(name, number, idantification_number,register_number);
		doctor->register_patients(patient);
		system("cls");
		cout << "挂号成功！挂号信息如下:" << endl;
		cout << "----------------------------------" << endl;
		cout << "    姓名：" << patient->get_name() << endl;
		cout << "电话号码：" << patient->get_number() << endl;
		cout << "身份证号：" << patient->get_identification_number() << endl;
		cout << "    序号：" << patient->get_register_number() << endl;
		cout << "----------------------------------" << endl;
		ofstream outfile("Hospital\\Patient.txt",ios::app);
		outfile << patient->get_name() << " "
			    << patient->get_number() << " "
			    << patient->get_identification_number() << " "
			    << patient->get_register_number() << " ";
		outfile.close();
	}
	return 1;
}