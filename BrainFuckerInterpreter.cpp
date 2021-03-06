#include<iostream>
#include<cstring>
/*  >	指针加一
    <	指针减一
    + 指针指向的字节的值加一
    - 指针指向的字节的值减一
    . 输出指针指向的单元内容（ASCII码）
    , 输入内容到指针指向的单元（ASCII码）
    [ 如果指针指向的单元值为零，向后跳转到对应的]指令的次一指令处
    ] 如果指针指向的单元值不为零，向前跳转到对应的[指令的次一指令处
*/
const int MAXSIZE = 10000;
using namespace std;
void parse(char*, int&, int&, char*, int*);//语法分析
int main()
{

    char str[MAXSIZE];//输入code
    int rel[MAXSIZE];//括号匹配跳转位置
    int pos = 0;//解释器对应指针
    int ptr = 0;//Brainfuck对应指针
    char arr[MAXSIZE];//Brainfuck对应Cell
    //初始化
    memset(str, 0, sizeof(str));
    memset(arr, 0, sizeof(arr));
    memset(rel, 0, sizeof(rel));
    cin.getline(str, MAXSIZE,'q');
    //对括号匹配的预处理，节约跳转时间
    int l = 0, end = strlen(str);
    while (l!=end) {
        while (l<end && str[l++] != '[');//寻找第一个[
        auto r = l;
        int count = 1;
        for (; r < end; r++)
        {
            if (str[r] == '[')count++;//剔除其中嵌套的[]对
            if (str[r] == ']') {
                count--; if (count == 0) {
                    r++; break;
                }
            }
        };//寻找匹配的]
        rel[l - 1] = r-1; rel[r - 1] = l-1;
    }
    //语法分析
    while (str[pos] != '\0') {
        parse(str, pos, ptr, arr, rel);
        pos++;
    }

    return 0;
}

void parse(char* str, int& pos, int &ptr, char *arr, int *rel)
{
    switch (str[pos])
    {
    case '>':
        ptr++; break;
    case '<':
        ptr--; break;
    case '+':
        arr[ptr]++; break;
    case '-':
        arr[ptr]--; break;
    case '.':
        cout <<arr[ptr]; break;
    case ',':
        cin >> arr[ptr]; break;
    case '[':
        if (!arr[ptr])pos = rel[pos]; break;
    case ']':
        pos = rel[pos]-1; break;//利用了'['的条件检测来达成跳转的作用
    default:
        break;
    }
}
