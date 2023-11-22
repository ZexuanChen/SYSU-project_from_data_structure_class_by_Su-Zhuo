#ifndef ImgProcess_H
#define ImgProcess_H
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <fstream>
#include <opencv2/opencv.hpp> //opencv库
using namespace std;

const int N = 256; //像素值默认是usigned char类型
class ImgProcess {
public:
    ImgProcess() { //构造函数
        clear();
    }
    ~ImgProcess() {} //析构函数 
    void clear(); //清空变量 
    bool img_read(string name); //读取图片 
    void img_show(); //显示图片
    void img_color_to_gray(); //转为灰度图 
    void resize(int w, int h);
    void encode(); //压缩图片，采用哈夫曼编码 
    void decode(string name); //解压缩 
private:
    cv::Mat img; //图片存储容器

    //压缩部分
    struct Node { //哈夫曼树节点 
        int pixel = 0, freq = 0, pos = -1; //像素值、出现次数、位置 
        int lchild = -1, rchild = -1;

        bool operator < (const Node& b) const {
            return freq > b.freq;
        }
    };
    int root; //哈夫曼树根 
    vector<Node> tree; //用vector存储哈夫曼树 
    string cg[N << 1]; //编码对照表 
};

//清空成员变量
void ImgProcess::clear()
{
    /*img无需清空*/
    for (auto& it : cg) it = "";
    tree.clear();
    root = 0;
}

//读取图像
bool ImgProcess::img_read(string name)
{
    img = cv::imread("project5_src_pic/"+name);
    if (img.empty()) return false;
    cout << "读取成功！\n";
    return true;
}

//显示图像 
void ImgProcess::img_show()
{
    cv::imshow("img", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

//彩图转灰度图 
void ImgProcess::img_color_to_gray()
{
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY); //转为灰度
    cout << "转换成功！\n";
    img_show();
    cv::imwrite("gray-block.png", img); //输出图片文件
    cout << "已保存！\n";
}

//改变大小（采用默认的线性插值）
void ImgProcess::resize(int w, int h)
{
    cv::imshow("another_img", img);
    
    cv::Size dsize(w, h);
    cv::resize(img, img, dsize); //改变大小
    cout << "大小更新成功！\n";
    img_show();
    cv::imwrite("another_size_pic.png", img);
    cout << "已保存！\n";
}

//压缩 
void ImgProcess::encode()
{
    if (img.type() == 16) cv::cvtColor(img, img, cv::COLOR_BGR2GRAY); //暂时只能存储灰度图

    priority_queue<Node> q; //用于创建哈夫曼树
    clear();
    tree.resize(N << 1);
    //统计图像的像素值的频率等相关信息
    int h = img.rows, w = img.cols, n = N - 1, cnt = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            tree[img.at<uchar>(i, j)].pos = img.at<uchar>(i, j);
            tree[img.at<uchar>(i, j)].pixel = img.at<uchar>(i, j);
            tree[img.at<uchar>(i, j)].freq++;
            if (tree[img.at<uchar>(i, j)].freq == 1) cnt++, q.push(tree[img.at<uchar>(i, j)]);
        }
    }

    //建哈夫曼树
    while (q.size() > 1) {
        n++;
        Node n1 = q.top();
        q.pop();
        Node n2 = q.top();
        q.pop();
        tree[n].pos = n, tree[n].lchild = n1.pos, tree[n].rchild = n2.pos, tree[n].freq = n1.freq+n2.freq;
        q.push(tree[n]);
    }

    string s; //暂存编码
    //递归进行哈夫曼编码
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
    root = q.top().pos; //哈夫曼树根的编号
    dfs(root);

    ofstream fout("data.txt"); //将压缩数据写入文件
    fout << w << ' ' << h << ' '; //写入图像的宽高信息
    //写入每一个像素点的像素值的编码
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fout << cg[img.at<uchar>(i, j)];
        }
    }

    cout << "已压缩！\n";
    fout.close();
}

//解压缩
void ImgProcess::decode(string name)
{
    ifstream fin(name);
    int w, h, posi = 0, posj = 0;
    string code;
    int pos = 0;
    fin >> w >> h;
    fin.close();
    img.create(w, h, CV_8UC1); //清空重写
   
    //进行哈夫曼解码
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

    //哈夫曼解码驱动
    for (; pos < code.size(); pos++) {
        dfs(root);
        posj++;
        if (posj >= w) posi++, posj = 0;
    }

    cout << "已解压！\n";
    img_show(); //显示图片
}
#endif
