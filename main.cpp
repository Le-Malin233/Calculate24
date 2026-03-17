#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Timer.H>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <stack>
#include <cctype>
#include <cmath>
#include <unordered_map>
#include <set>
#include <map>
#include <regex>
#include "Calculate24.cpp"


using namespace std;

static Fl_Group* Start_page;
static Fl_Group* mode1_introduce_page;
static Fl_Group* mode2_introduce_page;
static Fl_Group* mode3_introduce_page;
static Fl_Group* mode1_page;
static Fl_Group* mode1_answer;
static Fl_Group* mode2_3_basic_page;
static Fl_Group* mode2_page;
static Fl_Group* mode3_page;
Fl_Box* box12;
Fl_Box* box13;
Fl_Box* box14;
Fl_Box* box15;
Fl_Box* box17;
Fl_Box* box18;
Fl_Box* box19;
Fl_Box* box20;
Fl_Button* button12;
Fl_Button* button13;
Fl_Button* button14;
Fl_Button* button15;

string numbers;
string answer1;
string expre2;
string nums2;
vector<int> four_nums;
char ans[50] = {};
char nums_ch[20] = {};
char record[12] = {};
char score[11] = {};
char newrecd[3] = {};
int Time = 60;
int Record;
int Score;
bool counter_flag = false;
bool flag3 = false;
ifstream recordFile;


string cal24(string num);
void counter();
vector<int> four_numbers();
bool validateExpression(const std::string& expression, const std::vector<int>& numbers);
double evaluateExpression(const string& expr);

void enter_mode1(Fl_Widget* w, void* data) {
    Start_page->hide();
    mode1_introduce_page->show();
}
void start_mode1(Fl_Widget* w, void* data) {
    mode1_introduce_page->hide();
    mode1_page->show();
}
void enter_mode2(Fl_Widget* w, void* data) {
    Start_page->hide();
    mode2_introduce_page->show();
}
//定时器程序
void updateCountdown(void* data) {
    if (counter_flag) {
        Time = 60;
        return;
    }
    if (Time > 0) {
        Time--;
        stringstream ss;
        char aa[5] = {};
        if(Time>9){
            ss << "00:" << Time;
            box12->labelsize(40);
            box12->labelcolor(FL_BLACK);
        }
        else{ 
            ss << "00:0" << Time; 
            box12->labelsize(50);
            box12->labelcolor(FL_RED);
            
        }
        ss >> aa;
        box12->label(aa);
        box12->redraw();
        Fl::flush();
        Fl::repeat_timeout(1.0, updateCountdown);
    }
    else {
        box12->labelsize(40);
        box12->label("Time's up!");
        box12->redraw();
        Time = 60;
        box15->show();
        button12->deactivate();
        button13->show();
        return;
    }
}
void start_mode2(Fl_Widget* w, void* data) {
    mode2_introduce_page->hide();
    mode2_3_basic_page->show();
    mode2_page->show();
    box12->show();
    button12->activate();
    nums2 = "";
    four_nums = four_numbers();
    for (int i = 0; i < 4; ++i) {
        nums2 += to_string(four_nums[i]);
        nums2 += ' ';
    }
    for (int i = 0; i < 11; ++i) {
        nums_ch[i] = ' ';
    }
    for (int i = 0; i < nums2.size(); ++i) {
        nums_ch[i] = nums2[i];
    }
    box13->label(nums_ch);
    box13->show();
    box12->label("");
    counter_flag = false;
    Fl::repeat_timeout(1.0, updateCountdown); // 启动定时器
}
void enter_mode3(Fl_Widget* w, void* data) {
    Start_page->hide();
    mode3_introduce_page->show();
    
}
void start_mode3(Fl_Widget* w, void* data) {
    mode3_introduce_page->hide();
    mode2_3_basic_page->show();
    button14->show();
    recordFile.open("D:\\record.txt");
    string rec;
    recordFile >> rec;
    stringstream ss;
    ss << rec;
    ss >> Record;
    recordFile.close();
    string recd = "Record: " + to_string(Record);
    for (int i = 0; i < 11; ++i) {
        record[i] = ' ';
    }
    for (int i = 0; i < recd.size(); ++i) {
        record[i] = recd[i];
    }
    nums2 = "";
    Score = 0;
    four_nums = four_numbers();
    for (int i = 0; i < 4; ++i) {
        nums2 += to_string(four_nums[i]);
        nums2 += ' ';
    } 
    for (int i = 0; i < 11; ++i) {
        nums_ch[i] = ' ';
    }
    for (int i = 0; i < nums2.size(); ++i) {
        nums_ch[i] = nums2[i];
    }
    string sco = "Score: " + to_string(Score);
    for (int i = 0; i < 11; ++i) {
        score[i] = ' ';
    }
    for (int i = 0; i < sco.size(); ++i) {
        score[i] = sco[i];
    }
    mode3_page->show();
    box17->label(nums_ch);
    box17->show();
}
void return_button(Fl_Widget* w, void* data) {
    Start_page->show();
    mode1_introduce_page->hide();
    mode2_introduce_page->hide();
    mode3_introduce_page->hide();
}
void return_button1(Fl_Widget* w, void* data) {
    Start_page->show();
    mode1_page->hide();
    mode1_answer->hide();
    Fl_Input* input = (Fl_Input*)data;
    input->value("");
}
void mode1_work(Fl_Widget* w, void* data) {
    mode1_answer->hide();
    Fl_Input* input = (Fl_Input*)data;
    numbers = input->value();
    answer1 = cal24(numbers);
    for (int i = 0; i <20; ++i) {
        ans[i] = ' ';
    }
    for (int i = 0; i < answer1.size(); ++i) {
        ans[i] = answer1[i];
    }
    mode1_answer->show();
}
void mode2_work(Fl_Widget* w, void* data) {
    Fl_Input* input = (Fl_Input*)data;
    expre2 = input->value();
    bool flag=validateExpression(expre2, four_nums);
    if (flag) {
        if (evaluateExpression(expre2) == 24) {
            box14->show();
            box15->hide();
        }
        else {
            box15->show();
            box14->hide();
        }
    }
    else {
        box15->show();
        box14->hide();
    }
    button12->deactivate();
    button13->show();
    counter_flag = true;
}
void mode3_work(Fl_Widget* w, void* data) {
    Fl_Input* input = (Fl_Input*)data;
    expre2 = input->value();
    bool flag = validateExpression(expre2, four_nums);
    if (flag) {
        if (evaluateExpression(expre2) == 24) {
            Score++;
        }
        else {
            if (flag3) {
                box19->show();
                box20->show();
            }
            box18->show();
            button14->deactivate();
            return;
        }
    } else{
        if (flag3) {
            box19->show();
            box20->show();
        }
        box18->show();
        button14->deactivate();
        return;
    }
    string sco = "Score: " + to_string(Score);
    for (int i = 0; i < 11; ++i) {
        score[i] = ' ';
    }
    for (int i = 0; i < sco.size(); ++i) {
        score[i] = sco[i];
    } 
    if (Score > Record) {
        flag3 = true;
        Record = Score;
        string recd = "Record: " + to_string(Record);
        for (int i = 0; i < 11; ++i) {
            record[i] = ' ';
        }
        for (int i = 0; i < recd.size(); ++i) {
            record[i] = recd[i];
        }
        string newrec = to_string(Record);
        for (int i = 0; i < 3; ++i) {
            newrecd[i] = ' ';
        }
        for (int i = 0; i < newrec.size(); ++i) {
            newrecd[i] = newrec[i];
        }
        ofstream file("D:\\record.txt");
        file << to_string(Record);
        file.close();
    }
    input->value("");
    box17->hide();
    for (int i = 0; i < nums2.size(); ++i) {
        nums_ch[i] = ' ';
    }
    nums2 = "";
    four_nums = four_numbers();
    for (int i = 0; i < 4; ++i) {
        nums2 += to_string(four_nums[i]);
        nums2 += ' ';
    }
    for (int i = 0; i < nums2.size(); ++i) {
        nums_ch[i] = nums2[i];
    }
    box17->show();
}
void return_button2(Fl_Widget* w, void* data) {
    Start_page->show();
    mode2_3_basic_page->hide();
    mode2_page->hide();
    button13->hide();
    box12->hide();
    box13->hide();
    box14->hide();
    box15->hide();
    Fl_Input* input = (Fl_Input*)data;
    input->value("");
}

void return_button3(Fl_Widget* w, void* data) {
    Start_page->show();
    mode2_3_basic_page->hide();
    mode3_page->hide();
    button14->hide();
    button14->activate();
    box17->hide();
    box18->hide();
    box19->hide();
    box20->hide();
    Score = 0;
    flag3 = false;
    Fl_Input* input = (Fl_Input*)data;
    input->value("");
}


int main(int argc, char** argv) {
    Fl_Window* window = new Fl_Window(800, 600);
    window->label("Calculate 24 by Le Malin");                         		
    // 主界面
    Start_page = new Fl_Group(0, 0, 800, 600);
    Fl_Box* box1 = new Fl_Box(100, 30, 600, 200, "Calculate 24 !");
    //box1->box(FL_UP_BOX);
    box1->labelsize(72);
    box1->labelfont(FL_BOLD + FL_ITALIC);
    box1->labeltype(FL_SHADOW_LABEL);
    Fl_Button* button1 = new Fl_Button(286, 280, 240, 60, "Calculating Mode");
    button1->labelsize(25);
    Fl_Button* button2 = new Fl_Button(286, 380, 240, 60, "Challenge Mode");
    button2->labelsize(25);
    Fl_Button* button3 = new Fl_Button(286, 480, 240, 60, "Infinite Mode");
    button3->labelsize(25); 
    button1->callback(enter_mode1);
    button2->callback(enter_mode2);
    button3->callback(enter_mode3);
    Start_page->end();

    //mode1准备界面
    mode1_introduce_page = new Fl_Group(0, 0, 800, 600);
    Fl_Multiline_Output* text1 = new Fl_Multiline_Output(50, 120, 700, 300);
    text1->value("  You need to enter four numbers, ranging from 0 to \n13, where 11, 12, 13 can be replaced by J, Q, K,sep-\narate each number with \"  \". If they can be calculated \nto 24, the program will give one of the calculations.");
    text1->textsize(30);
    text1->box(FL_RFLAT_BOX);
    Fl_Box* box2 = new Fl_Box(100, 40, 600, 20, "Calculate 24 !");
    box2->labelsize(40);
    box2->labelfont(FL_BOLD + FL_ITALIC);
    box2->labeltype(FL_SHADOW_LABEL);
    Fl_Button* button4 = new Fl_Button(286, 500, 240, 60, "Continue");
    button4->labelsize(25);
    button4->callback(start_mode1);
    Fl_Button* button5 = new Fl_Button(2, 2, 60, 40, "Return");
    button5->callback(return_button);
    mode1_introduce_page->end();
    mode1_introduce_page->hide();

    //mode2准备界面
    mode2_introduce_page = new Fl_Group(0, 0, 800, 600);
    Fl_Multiline_Output* text2 = new Fl_Multiline_Output(50, 120, 700, 300);
    text2->value("  In this mode, four numbers are given on the screen,\nranging from 1 to 13. You need to enter the correct \nformula in 1 minute. If you enter it correctly, you win. \n( Note: The input formula should contain only the nu-\nmbers 1-13 and the symbol \" +  -  *  /  ( )\" ,such as \n\"3+3*(2+5)\".)When you click the \"Continue\" button,\nthe time will start.");
    text2->textsize(30);
    text2->box(FL_RFLAT_BOX);
    Fl_Box* box3 = new Fl_Box(100, 40, 600, 20, "Calculate 24 !");
    box3->labelsize(40);
    box3->labelfont(FL_BOLD + FL_ITALIC);
    box3->labeltype(FL_SHADOW_LABEL);
    Fl_Button* button6 = new Fl_Button(286, 500, 240, 60, "Continue");
    button6->labelsize(25);
    button6->callback(start_mode2);
    Fl_Button* button7 = new Fl_Button(2, 2, 60, 40, "Return");
    button7->callback(return_button);
    mode2_introduce_page->end();
    mode2_introduce_page->hide();
   
    //mode3准备界面
    mode3_introduce_page = new Fl_Group(0, 0, 800, 600);
    Fl_Multiline_Output* text3 = new Fl_Multiline_Output(50, 120, 700, 300);
    text3->value("  In this mode, four numbers are given on the screen,\nranging from 1 to 13. You need to enter the correct \nformula for every four numbers. If you enter correctly, \nyou will add 1 point. The game ends when you enter \nit wrong.(Note: The input formula should contain only \nthe numbers 1-13 and the symbol \" +  -  *  /  ( )\",such \nas \"3+(3*(2+5))\".)");
    text3->textsize(30);
    text3->box(FL_RFLAT_BOX);
    Fl_Box* box4 = new Fl_Box(100, 40, 600, 20, "Calculate 24 !");
    box4->labelsize(40);
    box4->labelfont(FL_BOLD + FL_ITALIC);
    box4->labeltype(FL_SHADOW_LABEL);
    Fl_Button* button8 = new Fl_Button(286, 500, 240, 60, "Continue");
    button8->labelsize(25);
    button8->callback(start_mode3);
    Fl_Button* button9 = new Fl_Button(2, 2, 60, 40, "Return");
    button9->callback(return_button);
    mode3_introduce_page->end();
    mode3_introduce_page->hide();

    //mode1界面
    mode1_page = new Fl_Group(0, 0, 800, 600);
    Fl_Box* box5 = new Fl_Box(100, 40, 600, 20, "Calculate 24 !");
    box5->labelsize(40);
    box5->labelfont(FL_BOLD + FL_ITALIC);
    box5->labeltype(FL_SHADOW_LABEL);
    Fl_Box* box6 = new Fl_Box(80, 100, 100, 20, "Input your numbers:");
    box6->labelsize(25);
    Fl_Input* input1 = new Fl_Input(150, 150,500, 200);
    input1->textsize(120);
    Fl_Button* button10 = new Fl_Button(286, 370, 240, 50, "Calculate");
    button10->labelsize(25);
    button10->callback(mode1_work,(void*)input1);
    mode1_page->end();
    mode1_page->hide();

    //mode1答案
    mode1_answer = new Fl_Group(0, 0, 800, 600);
    Fl_Box* box7 = new Fl_Box(100, 480, 600, 90, ans);
    box7->box(FL_UP_BOX);
    box7->labelsize(55);
    Fl_Box* box8 = new Fl_Box(80, 440, 100, 20, "The answer is:");
    box8->labelsize(25);
    Fl_Button* button11 = new Fl_Button(2, 2, 60, 40, "Return");
    button11->callback(return_button1,(void* )input1);
    mode1_answer->end();
    mode1_answer->hide();

    //mode2,3共用的输入界面
    mode2_3_basic_page = new Fl_Group(0, 0, 800, 600);
    Fl_Box* box9 = new Fl_Box(100, 40, 600, 20, "Calculate 24 !");
    box9->labelsize(40);
    box9->labelfont(FL_BOLD + FL_ITALIC);
    box9->labeltype(FL_SHADOW_LABEL);
    Fl_Box* box10 = new Fl_Box(80, 100, 100, 20, "The four numbers are:");
    box10->labelsize(25);
    Fl_Box* box11 = new Fl_Box(60, 250, 100, 20, "Enter your answer:");
    box11->labelsize(25);
    Fl_Input* input2 = new Fl_Input(100, 280, 600, 90);
    input2->textsize(70);
    mode2_3_basic_page->end();
    mode2_3_basic_page->hide();

    //mode2工作界面
    mode2_page =new Fl_Group(0, 0, 800, 600);
    button12 = new Fl_Button(286, 380, 240, 50, "Confirm");
    button12->labelsize(25);
    button12->callback(mode2_work, (void*)input2);
    Fl_Box* box12a = new Fl_Box(560, 10, 220, 80);
    box12a->box(FL_UP_BOX);
    box12 = new Fl_Box(560, 10, 220, 80);
    box12->labelsize(40);
    box12->labelfont(FL_BOLD);
    box12->hide();
    box13 = new Fl_Box(150, 85, 450, 200,nums_ch);
    box13->labelsize(80);
    box13->labelfont(FL_BOLD);
    box13->hide();
    box14 = new Fl_Box(150, 400, 500, 200,"YOU WIN!");
    box14->labelsize(80);
    box14->labelcolor(FL_GREEN);
    box14->hide();
    box15 = new Fl_Box(150, 400, 500, 200,"YOU LOSE!");
    box15->labelsize(80);
    box15->labelcolor(FL_RED);
    box15->hide();
    button13 = new Fl_Button(2, 2, 60, 40, "Return");
    button13->callback(return_button2, (void*)input2);
    button13->hide();
    mode2_page->end();
    mode2_page->hide();

    //mode3工作界面
    mode3_page = new Fl_Group(0, 0, 800, 600);
    button14 = new Fl_Button(286, 380, 240, 50, "Confirm");
    button14->labelsize(25);
    button14->callback(mode3_work, (void*)input2);
    Fl_Box* box16 = new Fl_Box(560, 10, 220, 80);
    box16->box(FL_UP_BOX);
    Fl_Box* box16a = new Fl_Box(560, 25, 220, 20,record);
    box16a->labelsize(25);
    Fl_Box* box16b = new Fl_Box(560, 55, 220, 20,score);
    box16b->labelsize(25);
    box17 = new Fl_Box(150, 85, 450, 200, nums_ch);
    box17->labelsize(80);
    box17->labelfont(FL_BOLD);
    box17->hide();
    box18 = new Fl_Box(150, 400, 500, 200, "Game Over!");
    box18->labelsize(80);
    box18->labelcolor(FL_RED);
    box18->hide();
    box19 = new Fl_Box(100, 550, 500, 50, "New Record:");
    box19->labelsize(40);
    box19->labelcolor(FL_GREEN);
    box19->hide();
    box20 = new Fl_Box(500, 550, 10, 50, newrecd);
    box20->labelsize(40);
    box20->labelcolor(FL_GREEN);
    box20->hide();
    button15 = new Fl_Button(2, 2, 60, 40, "Return");
    button15->callback(return_button3, (void*)input2);
    mode3_page->end();
    mode3_page->hide();

    window->end();
    window->show();

    return Fl::run();
}
 
