#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

class CourseExam
{
public:
    CourseExam()
    {
        _code = "";
        _name = "";
        _date = "";
        _hall = "";
    }
    CourseExam(string code, string name, string date, string hall)
    {
        _code = code;
        _name = name;
        _date = date;
        _hall = hall;
    }
    string getCode()
    {
        return _code;
    }
    string getName()
    {
        return _name;
    }
    string getDate()
    {
        return _date;
    }
    string getHall()
    {
        return _hall;
    }
    void setDate(string date)
    {
        _date = date;
    }
    void setHall(string hall)
    {
        _hall = hall;
    }
private:
    string _code;
    string _name;
    string _date;
    string _hall;
};

class Student
{
public:
    Student()
    {
        _id = 0;
        _name = "";
        _course_codes = "";
    }
    Student(int id, string name, string course_codes)
    {
        _id = id;
        _name = name;
        _course_codes = course_codes;

    }
    int getID()
    {
        return _id;
    }
    string getName()
    {
        return _name;
    }
    string getCourseCodes()
    {
        return _course_codes;
    }

private:
    int _id;
    string _name;
    string _course_codes;
};

class StudentsManager
{
public:
    StudentsManager()
    {
        _number_of_students = 0;
    }
    void addStudent(int id, string name, string course_codes)
    {
        Student tmp(id, name, course_codes);
        if (_number_of_students < 100)
            _students[_number_of_students++] = tmp;
    }
    int getNumber()
    {
        return _number_of_students;
    }
    int getMinStudentID()
    {
        SortByID();
        return _students[0].getID();
    }
    int getMaxStudentID()
    {
        SortByID();
        return _students[_number_of_students - 1].getID();
    }
    string getStudentsCodes(int index)
    {
        return _students[index].getCourseCodes();
    }
    int getStudentsIDS(int index)
    {
        return _students[index].getID();
    }
    string getDroppedStudentsIDs()
    {
        string dropped;
        SortByID();
        int start = _students[0].getID();
        int end = _students[_number_of_students - 1].getID();
        for (int i = start; i < end; i++)
        {
            if (StudentIDExist(i)) continue;
            dropped += to_string(i);
            dropped += "\n";
        }
        return dropped;
    }
    bool StudentIDExist(int ID)
    {
        for (int i = 0; i < _number_of_students; i++)
        {
            if (ID == _students[i].getID()) return true;
        }
        return false;
    }
    void SortByID()
    {
        Student term;
        for (int i = 0; i < _number_of_students; i++)
        {
            for (int j = 0; j < _number_of_students - 1; j++)
            {
                if (_students[j].getID()>_students[j + 1].getID())
                {
                    term = _students[j];
                    _students[j] = _students[j + 1];
                    _students[j + 1] = term;
                }
            }
        }
    }
    void getStudentCourses()
    {
        int ID;
        cin >> ID;
        string studentcourses;
        int count = 0;
        for (int i = 0; i < 100; i++)
        {
            if (_students[i].getID() == ID)
            {
                break;
            }
            else
            {
                count++;
            }
        }
        string courses = _students[count].getCourseCodes();
        string course;
        istringstream ss1(courses);
        while (getline(ss1, course, ','))
        {
            cout << course << endl;
        }
    }
    void getCoursesStudents()
    {
        string course;
        string code;
        cin >> code;
        for (int i = 0; i < 100; i++)
        {
            string courses = _students[i].getCourseCodes();
            istringstream ss1(courses);
            while (getline(ss1, course, ','))
            {
                if (course == code)
                {
                    cout << _students[i].getID() << endl;
                }

            }
        }
    }
    void ListStudents()
    {
        bool none = true;
        string value;
        int n;
        cin >> value >> n;
        for (int i = 0; i < _number_of_students; i++)
        {
            string tmp = _students[i].getCourseCodes();
            int count = countCourses(tmp);
            if (value == "More")
            {
                if (count > n)
                {
                    cout << _students[i].getID() << endl;
                    none = false;
                }

            }
            else if (value == "Less")
            {
                if (count < n)
                {
                    cout << _students[i].getID() << endl;
                    none = false;
                }


            }
            else if (value == "Equal")
            {
                if (count == n)
                {
                    cout << _students[i].getID() << endl;
                    none = false;
                }
            }
        }
        if (none == true)
        {
            cout << "none" << endl;
        }
    }

private:
    int _number_of_students;
    Student _students[100];
    int countCourses(string s)
    {
        int count = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ',')
            {
                count++;
            }
        }
        return (count + 1);
    }
};

class CoursesManager
{
public:
    CoursesManager()
    {
        _number_of_exams = 0;
    }
    void addCourse(string code, string name, string date, string hall)
    {
        CourseExam tmp(code, name, date, hall);
        if (_number_of_exams < 100)
            _courses[_number_of_exams++] = tmp;
    }
    int getNumber()
    {
        return _number_of_exams;
    }
    int getNumberOfHalls()
    {
        int counter = 0;
        string halls = "";
        for (int i = 0; i < _number_of_exams; i++)
        {
            string hall = _courses[i].getHall();
            if (halls.find(hall) == string::npos)
            {
                counter++;
                halls += hall + ";";
            }
        }
        return counter;
    }
    string getExamsStartDate()
    {
        SortByDate();
        return _courses[0].getDate();
    }
    string getExamsEndDate()
    {
        SortByDate();
        return _courses[_number_of_exams - 1].getDate();
    }
    int getExamsPeriodInDays()
    {
        return  DateToNumberDays(getExamsEndDate()) - DateToNumberDays(getExamsStartDate()) + 1;
    }
    void SortByDate()
    {
        CourseExam term;
        for (int i = 0; i < _number_of_exams; i++)
        {
            for (int j = 0; j < _number_of_exams - 1; j++)
            {
                if (DateToNumberDays(_courses[j].getDate()) > DateToNumberDays(_courses[j + 1].getDate()))
                {
                    term = _courses[j];
                    _courses[j] = _courses[j + 1];
                    _courses[j + 1] = term;
                }
            }
        }
    }
    void getCoursesByDate()
    {
        string tmp;
        string date;
        cin >> date;
        for (int i = 0; i < _number_of_exams; i++)
        {
            tmp = _courses[i].getDate();
            if (tmp == date)
            {
                cout << _courses[i].getCode() << endl;
            }
        }
    }
    void ListCourses(StudentsManager &students_manager)
    {
        bool none = true;
        string codes;
        string tmp;
        string code;
        string value;
        cin >> value;
        int n;
        cin >> n;
        int count;
        for (int i = 0; i < _number_of_exams; i++)
        {
            count = 0;
            code = _courses[i].getCode();
            for (int j = 0; j < students_manager.getNumber(); j++)
            {
                codes = students_manager.getStudentsCodes(j);
                istringstream ss1(codes);
                while (getline(ss1, tmp, ','))
                {
                    if (tmp == code)
                    {
                        count++;
                        break;
                    }
                }
            }
            if (value == "More")
            {
                if (count > n)
                {
                    cout << code << endl;
                    none = false;
                }
            }
            else if (value == "Less")
            {
                if (count < n)
                {
                    cout << code << endl;
                    none = false;

                }

            }
            else if (value == "Equal")
            {
                if (count == n)
                {
                    cout << code << endl;
                    none = false;
                }
            }
        }
        if (none == true)
        {
            cout << "none" << endl;
        }
    }
    void ListHallStudents(StudentsManager &students_manager)
    {
        int stds[25];
        int idx = 0;
        string data;
        string data2[2];
        int index = 0;
        cin >> data;
        istringstream ss2(data);
        while (getline(ss2, data2[index++], ',')) {}
        string codes;
        string tmp;
        string hall = data2[0];
        string date = data2[1];
        for (int i = 0; i < _number_of_exams; i++)
        {
            if (_courses[i].getHall() == hall && _courses[i].getDate() == date)
            {
                for (int m = 0; m < students_manager.getNumber(); m++)
                {
                    codes = students_manager.getStudentsCodes(m);
                    istringstream ss1(codes);
                    while (getline(ss1, tmp, ','))
                    {
                        if (tmp == _courses[i].getCode())
                        {
                            stds[idx++] = students_manager.getStudentsIDS(m);
                            break;
                        }
                    }
                }
            }
        }
        cout << stds[0] << endl;
        for (int i = 1; i < idx; i++)
        {
            bool matching = false;
            for (int j = 0; (j < i) && (matching == false); j++)if (stds[i] == stds[j]) matching = true;
            if (!matching) cout << stds[i] << endl;
        }
    }
    void ListStudentsAnyDay(StudentsManager &students_manager)
    {
        int stds[25];
        int idx = 0;
        string codes;
        string tmp;
        string hall;
        cin >> hall;
        for (int i = 0; i < _number_of_exams; i++)
        {
            if (_courses[i].getHall() == hall)
            {
                for (int m = 0; m < students_manager.getNumber(); m++)
                {
                    codes = students_manager.getStudentsCodes(m);
                    istringstream ss1(codes);
                    while (getline(ss1, tmp, ','))
                    {
                        if (tmp == _courses[i].getCode())
                        {
                            stds[idx++] = students_manager.getStudentsIDS(m);
                            break;
                        }
                    }
                }
            }
        }
        cout << stds[0] << endl;
        for (int i = 1; i < idx; i++)
        {
            bool matching = false;
            for (int j = 0; (j < i) && (matching == false); j++)if (stds[i] == stds[j]) matching = true;
            if (!matching) cout << stds[i] << endl;
        }
    }
    void ListStudentsAnyDate(StudentsManager &students_manager)
    {
        int stds[25];
        int idx = 0;
        int index = 0;
        string date;
        cin >> date;
        string codes;
        string tmp;
        for (int i = 0; i < _number_of_exams; i++)
        {
            if (_courses[i].getDate() == date)
            {
                for (int m = 0; m < students_manager.getNumber(); m++)
                {
                    codes = students_manager.getStudentsCodes(m);
                    istringstream ss1(codes);
                    while (getline(ss1, tmp, ','))
                    {
                        if (tmp == _courses[i].getCode())
                        {
                            stds[idx++] = students_manager.getStudentsIDS(m);
                            break;
                        }
                    }
                }
            }
        }
        cout << stds[0] << endl;
        for (int i = 1; i < idx; i++)
        {
            bool matching = false;
            for (int j = 0; (j < i) && (matching == false); j++)if (stds[i] == stds[j]) matching = true;
            if (!matching) cout << stds[i] << endl;
        }
    }
    void getStudyDays(StudentsManager &students_manager)
    {
        string data;
        cin >> data;
        string data2[2];
        int index = 0;
        istringstream ss1(data);
        while (getline(ss1, data2[index++], ',')) {}
        int ID = atof(data2[0].c_str());
        int n;
        for (int i = 0; i < students_manager.getNumber(); i++)
        {
            if (students_manager.getStudentsIDS(i) == ID)
            {
                n = i;
                break;
            }
        }
        string codes = students_manager.getStudentsCodes(n);
        string code[10];
        int index2 = 0;
        int index3;
        istringstream ss2(codes);
        while (getline(ss2, code[index2++], ','));
        string date;
        for (int i = 0; i < _number_of_exams; i++)
        {
            if (_courses[i].getCode() == data2[1])
            {
                date = _courses[i].getDate();
                break;
            }
        }
        string dates[10];
        int k = 0;
        for (int i = 0; i < index2; i++)
        {
            for (int j = 0; j < _number_of_exams; j++)
            {
                if (_courses[j].getCode() == code[i])
                {
                    dates[k++] = _courses[j].getDate();
                }
            }
        }
        string term;
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k - 1; j++)
            {
                if (DateToNumberDays(dates[j]) > DateToNumberDays(dates[j + 1]))
                {
                    term = dates[j];
                    dates[j] = dates[j + 1];
                    dates[j + 1] = term;
                }
            }
        }
        int y;
        for (int i = 0; i < k; i++)
        {
            if (dates[i] == date)
            {
                y = i;
            }
        }
        if (y == 0)
        {
            cout << "7" << endl;
        }
        else
        {
            if ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1 > 0)
            {
                cout << ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1) << endl;

            }
            else
                cout << "0" << endl;
        }
    }
    void ListStudyDaysStudents(StudentsManager &students_manager)
    {
        int students[30];
        int index = 0;
        string course;
        string code;
        cin >> code;
        for (int i = 0; i < students_manager.getNumber(); i++)
        {
            string courses = students_manager.getStudentsCodes(i);
            istringstream ss1(courses);
            while (getline(ss1, course, ','))
            {
                if (course == code)
                {
                    students[index++] = students_manager.getStudentsIDS(i);
                }

            }
        }
        for (int i = 0; i < index; i++)
        {
            int ID = students[i];
            int n;
            for (int i = 0; i < students_manager.getNumber(); i++)
            {
                if (students_manager.getStudentsIDS(i) == ID)
                {
                    n = i;
                    break;
                }
            }
            string codes = students_manager.getStudentsCodes(n);
            string _code[30];
            int index2 = 0;
            int index3;
            istringstream ss2(codes);
            while (getline(ss2, _code[index2++], ','));
            string date;
            for (int i = 0; i < _number_of_exams; i++)
            {
                if (_courses[i].getCode() == code)
                {
                    date = _courses[i].getDate();
                    break;
                }
            }
            string dates[30];
            int k = 0;
            for (int i = 0; i < index2; i++)
            {
                for (int j = 0; j < _number_of_exams; j++)
                {
                    if (_courses[j].getCode() == _code[i])
                    {
                        dates[k++] = _courses[j].getDate();
                    }
                }
            }
            string term;
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < k - 1; j++)
                {
                    if (DateToNumberDays(dates[j]) > DateToNumberDays(dates[j + 1]))
                    {
                        term = dates[j];
                        dates[j] = dates[j + 1];
                        dates[j + 1] = term;
                    }
                }
            }
            int y;
            for (int i = 0; i < k; i++)
            {
                if (dates[i] == date)
                {
                    y = i;
                }
            }
            if (y == 0)
            {
                cout << students[i] << " " << "7" << endl;
            }
            else
            {
                if ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1 > 0)
                {
                    cout << students[i] << " " << ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1) << endl;

                }
                else
                    cout << students[i] << " " << "0" << endl;
            }
        }
    }
    void ListStudyDaysCourses(StudentsManager &students_manager)
    {
        int ID;
        cin >> ID;
        int count = 0;
        for (int i = 0; i < 100; i++)
        {
            if (students_manager.getStudentsIDS(i) == ID)
            {
                break;
            }
            else
            {
                count++;
            }
        }
        string _courses1 = students_manager.getStudentsCodes(count);
        string _course[10];
        int idx = 0;
        istringstream ss1(_courses1);
        while (getline(ss1, _course[idx++], ','));
        for (int p = 0; p < idx - 1; p++)
        {
            string date;
            for (int i = 0; i < _number_of_exams; i++)
            {
                if (_courses[i].getCode() == _course[p])
                {
                    date = _courses[i].getDate();
                    break;
                }
            }
            string dates[10];
            int k = 0;
            for (int i = 0; i < idx; i++)
            {
                for (int j = 0; j < _number_of_exams; j++)
                {
                    if (_courses[j].getCode() == _course[i])
                    {
                        dates[k++] = _courses[j].getDate();
                    }
                }
            }
            string term;
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < k - 1; j++)
                {
                    if (DateToNumberDays(dates[j]) > DateToNumberDays(dates[j + 1]))
                    {
                        term = dates[j];
                        dates[j] = dates[j + 1];
                        dates[j + 1] = term;
                    }
                }
            }
            int y;
            for (int i = 0; i < k; i++)
            {
                if (dates[i] == date)
                {
                    y = i;
                }
            }
            if (y == 0)
            {
                cout << _course[p] << " " << "7" << endl;
            }
            else
            {
                if ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1 > 0)
                {
                    cout << _course[p] << " " << ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1) << endl;

                }
                else
                    cout << _course[p] << " " << "0" << endl;
            }
        }
    }
    void minimumStudyDays(StudentsManager &students_manager)
    {
        int ID;
        cin >> ID;
        int count = 0;
        for (int i = 0; i < 100; i++)
        {
            if (students_manager.getStudentsIDS(i) == ID)
            {
                break;
            }
            else
            {
                count++;
            }
        }
        string _courses1 = students_manager.getStudentsCodes(count);
        string _course[10];
        int idx = 0;
        istringstream ss1(_courses1);
        while (getline(ss1, _course[idx++], ','));
        int p = 0;
        string studydays[10][2];
        for (p ; p < idx - 1; p++)
        {
            string date;
            for (int i = 0; i < _number_of_exams; i++)
            {
                if (_courses[i].getCode() == _course[p])
                {
                    date = _courses[i].getDate();
                    break;
                }
            }
            string dates[10];
            int k = 0;
            for (int i = 0; i < idx; i++)
            {
                for (int j = 0; j < _number_of_exams; j++)
                {
                    if (_courses[j].getCode() == _course[i])
                    {
                        dates[k++] = _courses[j].getDate();
                    }
                }
            }
            string term;
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < k - 1; j++)
                {
                    if (DateToNumberDays(dates[j]) > DateToNumberDays(dates[j + 1]))
                    {
                        term = dates[j];
                        dates[j] = dates[j + 1];
                        dates[j + 1] = term;
                    }
                }
            }
            int y;
            for (int i = 0; i < k; i++)
            {
                if (dates[i] == date)
                {
                    y = i;
                }
            }
            if (y == 0)
            {
                studydays[p][0] = _course[p];
                studydays[p][1] = "7";
            }
            else
            {
                if ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1 > 0)
                {
                    studydays[p][0] = _course[p];
                    int v = ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1);
                    stringstream ss;
                    ss << v;
                    studydays[p][1] = ss.str();
                }
                else
                {
                    studydays[p][0] = _course[p];
                    studydays[p][1] = "0";
                }
            }
        }
        string studydays2[10];
        for (int i = 0; i < p; i++)
        {
            studydays2[i] = studydays[i][1];
        }
        int studydays3[10];
        for (int i = 0; i < 10; i++)
        {
            studydays3[i] = 0;
        }
        for (int i = 0; i < p; i++)
        {
            studydays3[i] = atof(studydays2[i].c_str());
        }
        int term;
        for (int i = 0; i < 9; i++)
        {
            for (int j = i + 1; j < 10; j++)
            {
                if (studydays3[i] > studydays3[j])
                {
                    term = studydays3[i];
                    studydays3[i] = studydays3[j];
                    studydays3[j] = term;
                }
            }
        }
        int c = countCourses(_courses1);
        for (int i = 0; i < p; i++)
        {
            if (studydays3[10 - c] == atof(studydays[i][1].c_str()))
            {
                cout << studydays[i][0] << " " << studydays3[10 - c] << endl;
                break;
            }
        }
    }
    void listMinimumCourses(StudentsManager &students_manager)
    {
        int studydays[30];
        for (int i = 0; i < 30; i++)
        {
            studydays[i] = 0;
        }
        int students[30];
        for (int i = 0; i < 30; i++)
        {
            students[i] = 0;
        }
        int index = 0;
        string course;
        string code;
        cin >> code;
        for (int i = 0; i < students_manager.getNumber(); i++)
        {
            string courses = students_manager.getStudentsCodes(i);
            istringstream ss1(courses);
            while (getline(ss1, course, ','))
            {
                if (course == code)
                {
                    students[index++] = students_manager.getStudentsIDS(i);
                }

            }
        }
        for (int i = 0; i < index; i++)
        {
            int ID = students[i];
            int n;
            for (int i = 0; i < students_manager.getNumber(); i++)
            {
                if (students_manager.getStudentsIDS(i) == ID)
                {
                    n = i;
                    break;
                }
            }
            string codes = students_manager.getStudentsCodes(n);
            string _code[30];
            int index2 = 0;
            int index3;
            istringstream ss2(codes);
            while (getline(ss2, _code[index2++], ','));
            string date;
            for (int i = 0; i < _number_of_exams; i++)
            {
                if (_courses[i].getCode() == code)
                {
                    date = _courses[i].getDate();
                    break;
                }
            }
            string dates[30];
            int k = 0;
            for (int i = 0; i < index2; i++)
            {
                for (int j = 0; j < _number_of_exams; j++)
                {
                    if (_courses[j].getCode() == _code[i])
                    {
                        dates[k++] = _courses[j].getDate();
                    }
                }
            }
            string term;
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < k - 1; j++)
                {
                    if (DateToNumberDays(dates[j]) > DateToNumberDays(dates[j + 1]))
                    {
                        term = dates[j];
                        dates[j] = dates[j + 1];
                        dates[j + 1] = term;
                    }
                }
            }
            int y;
            for (int i = 0; i < k; i++)
            {
                if (dates[i] == date)
                {
                    y = i;
                }
            }
            if (y == 0)
            {
                studydays[i] = 7;
            }
            else
            {
                if ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1 > 0)
                {
                    studydays[i] = ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1);
                }
                else
                    studydays[i] = 0;
            }
        }
        int term;
        for (int i = 0; i < 29; i++)
        {
            for (int j = i + 1; j < 30; j++)
            {
                if (studydays[i] > studydays[j])
                {
                    term = studydays[i];
                    studydays[i] = studydays[j];
                    studydays[j] = term;
                }
            }
        }
        cout << studydays[30 - index] << endl;
    }
    void getMinimumstudydays (StudentsManager &students_manager)
    {
        int studydays2[20];
        for (int i = 0; i < 20; i++)
        {
            studydays2[i] = 0;
        }
        for (int e = 0; e < _number_of_exams; e++)
        {
            int students[20];
            for (int i = 0; i < 10; i++)
            {
                students[i] = 0;
            }
            int index = 0;
            string course;
            string code;
            int studydays[20];
            for (int i = 0; i < 20; i++)
            {
                studydays[i] = 0;
            }
            code = _courses[e].getCode();
            for (int i = 0; i < students_manager.getNumber(); i++)
            {
                string courses = students_manager.getStudentsCodes(i);
                istringstream ss1(courses);
                while (getline(ss1, course, ','))
                {
                    if (course == code)
                    {
                        students[index++] = students_manager.getStudentsIDS(i);
                    }

                }
            }
            for (int i = 0; i < index; i++)
            {
                int ID = students[i];
                int n;
                for (int i = 0; i < students_manager.getNumber(); i++)
                {
                    if (students_manager.getStudentsIDS(i) == ID)
                    {
                        n = i;
                        break;
                    }
                }
                string codes = students_manager.getStudentsCodes(n);
                string _code[20];
                int index2 = 0;
                int index3;
                istringstream ss2(codes);
                while (getline(ss2, _code[index2++], ','));
                string date;
                for (int i = 0; i < _number_of_exams; i++)
                {
                    if (_courses[i].getCode() == code)
                    {
                        date = _courses[i].getDate();
                        break;
                    }
                }
                string dates[20];
                int k = 0;
                for (int i = 0; i < index2; i++)
                {
                    for (int j = 0; j < _number_of_exams; j++)
                    {
                        if (_courses[j].getCode() == _code[i])
                        {
                            dates[k++] = _courses[j].getDate();
                        }
                    }
                }
                string term;
                for (int i = 0; i < k; i++)
                {
                    for (int j = 0; j < k - 1; j++)
                    {
                        if (DateToNumberDays(dates[j]) > DateToNumberDays(dates[j + 1]))
                        {
                            term = dates[j];
                            dates[j] = dates[j + 1];
                            dates[j + 1] = term;
                        }
                    }
                }
                int y;
                for (int i = 0; i < k; i++)
                {
                    if (dates[i] == date)
                    {
                        y = i;
                    }
                }
                if (y == 0)
                {
                    studydays[i] = 7;
                }
                else
                {
                    if ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1 > 0)
                    {
                        studydays[i] = ((DateToNumberDays(dates[y]) - DateToNumberDays(dates[y - 1])) - 1);
                    }
                    else
                        studydays[i] = 0;
                }
            }
            int term;
            for (int i = 0; i < 19; i++)
            {
                for (int j = i + 1; j < 20; j++)
                {
                    if (studydays[i] > studydays[j])
                    {
                        term = studydays[i];
                        studydays[i] = studydays[j];
                        studydays[j] = term;
                    }
                }
            }
            studydays2[e] = studydays[20 - index];
        }
        int term;
        for (int i = 0; i < 19; i++)
        {
            for (int j = i + 1; j < 20; j++)
            {
                if (studydays2[i] > studydays2[j])
                {
                    term = studydays2[i];
                    studydays2[i] = studydays2[j];
                    studydays2[j] = term;
                }
            }
        }
        cout << studydays2[20 - _number_of_exams] << endl;
    }
    void ExamsSameDay(StudentsManager &students_manager)
    {
        bool none = true;
        int ID;
        cin >> ID;
        int q = 0;
        for (q; q < students_manager.getNumber(); q++)
        {
            if (students_manager.getStudentsIDS(q) == ID)
            {
                break;
            }
        }
        string codes = students_manager.getStudentsCodes(q);
        string _code[10][2];
        int index = 0;
        istringstream ss2(codes);
        while (getline(ss2, _code[index++][0], ','));
        for (int i = 0; i < index; i++)
        {
            for (int j = 0; j < _number_of_exams; j++)
            {
                if (_code[i][0] == _courses[j].getCode())
                {
                    _code[i][1] = _courses[j].getDate();
                    break;
                }
            }
        }
        string course[10];
        int count = 0;
        for (int i = 0; i < index - 1; i++)
        {
            for (int j = i + 1; j < index - 1; j++)
            {
                if (_code[i][1] == _code[j][1])
                {
                    course[count++] = _code[i][0];
                    course[count++] = _code[j][0];
                    none = false;
                }
            }
        }
        if (none == true)
            cout << "none" << endl;
        else
        {
            for (int i = 0; i < count; i++)
            {
                cout << course[i] << endl;
            }
        }
    }
    void ExamsSameDayStudents(StudentsManager &students_manager)
    {
        for (int k = 0; k < students_manager.getNumber(); k++)
        {
            bool none = true;
            int ID = students_manager.getStudentsIDS(k);
            int q = 0;
            for (q; q < students_manager.getNumber(); q++)
            {
                if (students_manager.getStudentsIDS(q) == ID)
                {
                    break;
                }
            }
            string codes = students_manager.getStudentsCodes(q);
            string _code[10][2];
            int index = 0;
            istringstream ss2(codes);
            while (getline(ss2, _code[index++][0], ','));
            for (int i = 0; i < index; i++)
            {
                for (int j = 0; j < _number_of_exams; j++)
                {
                    if (_code[i][0] == _courses[j].getCode())
                    {
                        _code[i][1] = _courses[j].getDate();
                        break;
                    }
                }
            }
            string course[10];
            int count = 0;
            for (int i = 0; i < index ; i++)
            {
                for (int j = i + 1; j < index; j++)
                {
                    if (_code[i][1] == _code[j][1])
                    {
                        course[count++] = _code[i][0];
                        course[count++] = _code[j][0];
                        none = false;
                    }
                }
            }
            if (none == true)
            {
                cout << students_manager.getStudentsIDS(k) << " " << "none" << endl;
            }
            else
            {
                cout << students_manager.getStudentsIDS(k) << " ";
                for (int i = 0; i < count; i++)
                {
                    cout << course[i] << " ";
                }
                cout << endl;
            }
        }
    }
    void ListExamSameHall(StudentsManager &students_manager)
    {
        bool none = true;
        string codes[10][2];
        int count1 = 0, count2 = 0;
        string date;
        cin >> date;
        int q = 0;
        for (q; q < _number_of_exams; q++)
        {
            if (_courses[q].getDate() == date)
            {
                codes[count1++][0] = _courses[q].getCode();
                codes[count2++][1] = _courses[q].getHall();
            }
        }
        string course[10];
        int count = 0;
        for (int i = 0; i < count1; i++)
        {
            for (int j = i + 1; j < count1; j++)
            {
                if (codes[i][1] == codes[j][1])
                {
                    course[count++] = codes[i][0];
                    course[count++] = codes[j][0];
                    none = false;
                }
            }
        }
        if (none == true)
        {
            cout << "none" << endl;
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                cout << course[i] << endl;
            }
        }
    }
    void ListExamSameHallAnyDay(StudentsManager &students_manager)
    {
        string _dates[10];
        string _dates2[10];
        int numb = 0;
        for (int i = 0; i < _number_of_exams; i++)
        {
            _dates[i] = _courses[i].getDate();
        }
        _dates2[numb++] = _dates[0];
        for (int i = 1; i < _number_of_exams; i++)
        {
            bool matching = false;
            for (int j = 0; (j < i) && (matching == false); j++)if (_dates[i] == _dates[j]) matching = true;
            if (!matching)  _dates2[numb++] = _dates[i];
        }
        for (int a = 0; a < numb ; a++)
        {
            bool none = true;
            string codes[10][2];
            int count1 = 0, count2 = 0;
            string date = _dates2[a];
            int q = 0;
            for (q; q < _number_of_exams; q++)
            {
                if (_courses[q].getDate() == date)
                {
                    codes[count1++][0] = _courses[q].getCode();
                    codes[count2++][1] = _courses[q].getHall();
                }
            }
            string course[10];
            int count = 0;
            for (int i = 0; i < count1; i++)
            {
                for (int j = i + 1; j < count1; j++)
                {
                    if (codes[i][1] == codes[j][1])
                    {
                        course[count++] = codes[i][0];
                        course[count++] = codes[j][0];
                        none = false;
                    }
                }
            }
            if (none == true)
                cout << date << " " << "none" << endl;
            else
            {
                cout << date << " ";
                for (int i = 0; i < count; i++)
                {
                    cout << course[i] << " ";
                }
                cout << endl;
            }
        }
    }
    void RescheduleSameHallDifferentDay(StudentsManager &students_mangager)
    {

    }
private:
    int _number_of_exams;
    CourseExam _courses[100];
    int countCourses(string s)
    {
        int count = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ',')
            {
                count++;
            }
        }
        return (count + 1);
    }
    int DateToNumberDays(string date)
    {
        string data[3];
        int index = 0;
        istringstream ss1(date);
        while (getline(ss1, data[index++], '/'));
        return atof(data[0].c_str()) + MonthToDays((atof(data[1].c_str()) - 1), atof(data[2].c_str()));
    }
    int MonthToDays(int month , int year)
    {
        const int days2010[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        const int days2011[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        const int days2012[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
        const int days2013[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        const int days2014[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        const int days2015[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        const int days2016[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
        int total = 0;
        if (year == 2016)
        {
            for (int i = 0; i < month; i++) total += days2016[i];

        }
        if (year == 2015)
        {
            for (int i = 0; i < month; i++) total += days2015[i];

        }
        if (year == 2014)
        {
            for (int i = 0; i < month; i++) total += days2014[i];

        }
        if (year == 2013)
        {
            for (int i = 0; i < month; i++) total += days2013[i];

        }
        if (year == 2012)
        {
            for (int i = 0; i < month; i++) total += days2012[i];

        }
        if (year == 2011)
        {
            for (int i = 0; i < month; i++) total += days2011[i];

        }
        if (year == 2010)
        {
            for (int i = 0; i < month; i++) total += days2010[i];

        }

        return total;
    }
};

void inputCourseExams(CoursesManager &courses_manager)
{
    string course_exams;
    string course;
    string course_data[4];
    int data_index;
    getline(cin, course_exams);
    //course_exams = "CoursesExams=[HUM001,Technical Writing,28/4/2016,HallA;CSE121,Computer Programming,3/5/2016,HallA;PHM110,Math 3,5/5/2016,HallC;PHM103,Physics,5/5/2016,HallA;EPM120,Electrical Circuits,6/5/2016,HallD;ECE132,Electronics,7/5/2016,HallB;CSE432,Computer Security,28/4/2016,HallA";
    course_exams = course_exams.substr(course_exams.find('[') + 1, course_exams.find(']') - course_exams.find('[') - 1);
    istringstream ss1(course_exams);
    while (getline(ss1, course, ';'))
    {
        istringstream ss2(course);
        data_index = 0;
        while (getline(ss2, course_data[data_index++], ','));
        courses_manager.addCourse(course_data[0], course_data[1], course_data[2], course_data[3]);
    }
}

void inputStudents(StudentsManager &students_manager)
{
    string students;
    string student;
    string student_data[3];
    int data_index;
    getline(cin, students);
    //students = "Students=[12001,Ahmed Hassan, (CSE121,HUM001,PHM110);12002,Aly Hamed,(CSE121,PHM110,PHM103);12003,Ayman Ali,(PHM110,EPM120,ECE132);12006,Hazem Elshenawy,(PHM103,ECE132);12007,Ahmed Gabr,(CSE432)";
    students = students.substr(students.find('[') + 1, students.find(']') - students.find('[') - 1);
    istringstream ss1(students);
    while (getline(ss1, student, ';'))
    {
        istringstream ss2(student);
        data_index = 0;
        student_data[2] = student.substr(student.find('(') + 1, student.find(')') - student.find('(') - 1);
        while (getline(ss2, student_data[data_index++], ','))
        {
            if (data_index == 2)
                break;
        }
        students_manager.addStudent(atoi(student_data[0].c_str()), student_data[1], student_data[2]);
    }

}

void takeOperations(CoursesManager &courses_manager, StudentsManager &students_manager)
{
    while (1)
    {
        string operation;
        cin >> operation;
        if (operation == "Quit")
        {
            cout << "Thanks!";
            return;
        }
        else if (operation == "Number_Students")
        {
            cout << students_manager.getNumber() << endl;
        }

        else if (operation == "Number_Courses")
        {
            cout << courses_manager.getNumber() << endl;
        }
        else if (operation == "Number_Halls")
        {
            cout << courses_manager.getNumberOfHalls() << endl;
        }
        else if (operation == "Student_ID_Min")
        {
            cout << students_manager.getMinStudentID() << endl;
        }
        else if (operation == "Student_ID_Max")
        {
            cout << students_manager.getMaxStudentID() << endl;
        }
        else if (operation == "Students_Dropped_IDs")
        {
            cout << students_manager.getDroppedStudentsIDs();
        }
        else if (operation == "Exams_Start_Date")
        {
            cout << courses_manager.getExamsStartDate() << endl;
        }
        else if (operation == "Exams_End_Date")
        {
            cout << courses_manager.getExamsEndDate() << endl;
        }
        else if (operation == "Exams_Period_InDays")
        {
            cout << courses_manager.getExamsPeriodInDays() << endl;
        }
        else if (operation == "Student_Courses")
        {
            students_manager.getStudentCourses();
        }
        else if (operation == "Course_Students")
        {
            students_manager.getCoursesStudents();
        }
        else if (operation == "List_Course_Students")
        {
            courses_manager.ListCourses(students_manager);
        }
        else if (operation == "List_Student_Courses")
        {
            students_manager.ListStudents();
        }
        else if (operation == "List_Hall_Students")
        {
            courses_manager.ListHallStudents(students_manager);
        }
        else if (operation == "List_Hall_Students_InAnyday")
        {
            courses_manager.ListStudentsAnyDay(students_manager);
        }
        else if (operation == "List_Day_Students_InAnyHall")
        {
            courses_manager.ListStudentsAnyDate(students_manager);
        }
        else if (operation == "List_Exams")
        {
            courses_manager.getCoursesByDate();
        }
        else if (operation == "List_StudyDays")
        {
            courses_manager.getStudyDays(students_manager);
        }
        else if (operation == "List_StudyDays_ForEveryStudent")
        {
            courses_manager.ListStudyDaysStudents(students_manager);
        }
        else if (operation == "List_StudyDays_ForEveryCourse")
        {
            courses_manager.ListStudyDaysCourses(students_manager);
        }
        else if (operation == "List_Minimum_Student_StudyDays")
        {
            courses_manager.minimumStudyDays(students_manager);
        }
        else if (operation == "List_Minimum_Course_StudyDays")
        {
            courses_manager.listMinimumCourses(students_manager);
        }
        else if (operation == "List_Minimum_StudyDays")
        {
            courses_manager.getMinimumstudydays(students_manager);
        }
        else if (operation == "List_Exam_InSameDay")
        {
            courses_manager.ExamsSameDay(students_manager);
        }
        else if (operation == "List_Exam_InSameDay_ForEveryStudent")
        {
            courses_manager.ExamsSameDayStudents(students_manager);
        }
        else if (operation == "List_Exam_InSameHall")
        {
            courses_manager.ListExamSameHall(students_manager);
        }
        else if (operation == "List_Exam_InSameHall_Simultaneously_InAnyDay")
        {
            courses_manager.ListExamSameHallAnyDay(students_manager);
        }

    }
}

int main()
{
    CoursesManager courses_manager;
    StudentsManager students_manager;
    inputCourseExams(courses_manager);
    inputStudents(students_manager);
    takeOperations(courses_manager, students_manager);
    return 0;
}
