#ifndef ImgProcess_H
#define ImgProcess_H
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <fstream>
#include <opencv2/opencv.hpp> //opencv��
using namespace std;

const int N = 256; //����ֵĬ����usigned char����
class ImgProcess {
public:
    ImgProcess() { //���캯��
        clear();
    }
    ~ImgProcess() {} //�������� 
    void clear(); //��ձ��� 
    bool img_read(string name); //��ȡͼƬ 
    void img_show(); //��ʾͼƬ
    void img_color_to_gray(); //תΪ�Ҷ�ͼ 
    void resize(int w, int h);
    void encode(); //ѹ��ͼƬ�����ù��������� 
    void decode(string name); //��ѹ�� 
private:
    cv::Mat img; //ͼƬ�洢����

    //ѹ������
    struct Node { //���������ڵ� 
        int pixel = 0, freq = 0, pos = -1; //����ֵ�����ִ�����λ�� 
        int lchild = -1, rchild = -1;

        bool operator < (const Node& b) const {
            return freq > b.freq;
        }
    };
    int root; //���������� 
    vector<Node> tree; //��vector�洢�������� 
    string cg[N << 1]; //������ձ� 
};

//��ճ�Ա����
void ImgProcess::clear()
{
    /*img�������*/
    for (auto& it : cg) it = "";
    tree.clear();
    root = 0;
}

//��ȡͼ��
bool ImgProcess::img_read(string name)
{
    img = cv::imread("project5_src_pic/"+name);
    if (img.empty()) return false;
    cout << "��ȡ�ɹ���\n";
    return true;
}

//��ʾͼ�� 
void ImgProcess::img_show()
{
    cv::imshow("img", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

//��ͼת�Ҷ�ͼ 
void ImgProcess::img_color_to_gray()
{
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY); //תΪ�Ҷ�
    cout << "ת���ɹ���\n";
    img_show();
    cv::imwrite("gray-block.png", img); //���ͼƬ�ļ�
    cout << "�ѱ��棡\n";
}

//�ı��С������Ĭ�ϵ����Բ�ֵ��
void ImgProcess::resize(int w, int h)
{
    cv::imshow("another_img", img);
    
    cv::Size dsize(w, h);
    cv::resize(img, img, dsize); //�ı��С
    cout << "��С���³ɹ���\n";
    img_show();
    cv::imwrite("another_size_pic.png", img);
    cout << "�ѱ��棡\n";
}

//ѹ�� 
void ImgProcess::encode()
{
    if (img.type() == 16) cv::cvtColor(img, img, cv::COLOR_BGR2GRAY); //��ʱֻ�ܴ洢�Ҷ�ͼ

    priority_queue<Node> q; //���ڴ�����������
    clear();
    tree.resize(N << 1);
    //ͳ��ͼ�������ֵ��Ƶ�ʵ������Ϣ
    int h = img.rows, w = img.cols, n = N - 1, cnt = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            tree[img.at<uchar>(i, j)].pos = img.at<uchar>(i, j);
            tree[img.at<uchar>(i, j)].pixel = img.at<uchar>(i, j);
            tree[img.at<uchar>(i, j)].freq++;
            if (tree[img.at<uchar>(i, j)].freq == 1) cnt++, q.push(tree[img.at<uchar>(i, j)]);
        }
    }

    //����������
    while (q.size() > 1) {
        n++;
        Node n1 = q.top();
        q.pop();
        Node n2 = q.top();
        q.pop();
        tree[n].pos = n, tree[n].lchild = n1.pos, tree[n].rchild = n2.pos, tree[n].freq = n1.freq+n2.freq;
        q.push(tree[n]);
    }

    string s; //�ݴ����
    //�ݹ���й���������
    function<void(int)> dfs = [&] (int now) {
        if (tree[now].lchild == -1) {
            cg[tree[now].pixel] = s;
            return;
        }

        s.push_back('0');
        dfs(tree[now].lchild);
        s.pop_back();
        s.push_back('1');
        dfs(tree[now].rchild);
        s.pop_back();
    };
    root = q.top().pos; //�����������ı��
    dfs(root);

    ofstream fout("data.txt"); //��ѹ������д���ļ�
    fout << w << ' ' << h << ' '; //д��ͼ��Ŀ����Ϣ
    //д��ÿһ�����ص������ֵ�ı���
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fout << cg[img.at<uchar>(i, j)];
        }
    }

    cout << "��ѹ����\n";
    fout.close();
}

//��ѹ��
void ImgProcess::decode(string name)
{
    ifstream fin(name);
    int w, h, posi = 0, posj = 0;
    string code;
    int pos = 0;
    fin >> w >> h;
    fin.close();
    img.create(w, h, CV_8UC1); //�����д
   
    //���й���������
    function<void(int)> dfs = [&] (int now) {
        if (tree[now].lchild == -1) {
            img.at<uchar>(posi, posj) = tree[now].pixel;
            return;
        }

        if (pos >= code.size()) return;

        if (code[pos] == '0') {
            pos++;
            dfs(tree[now].lchild);
        }
        else {
            pos++;
            dfs(tree[now].rchild);
        }
    };

    //��������������
    for (; pos < code.size(); pos++) {
        dfs(root);
        posj++;
        if (posj >= w) posi++, posj = 0;
    }

    cout << "�ѽ�ѹ��\n";
    img_show(); //��ʾͼƬ
}
#endif
