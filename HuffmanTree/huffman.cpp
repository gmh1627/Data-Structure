#include<iostream>
#include<string.h>

using namespace std;

typedef struct node{
    long long int weight;
    int parent, lchild, rchild;
}HTNode, *HuffmanTree;

typedef struct {
    char character;
    char* huffmanCode;
} HuffmanMap;

HuffmanMap huffmanMap[56];

typedef char **HuffmanCode;

HuffmanTree HT=NULL;
HuffmanCode HC=NULL;
char character[56]={' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
                'p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E',
                'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U',
                'V','W','X','Y','Z',',','.','\''};
                
void Select(HuffmanTree HT, int n, int &s1, int &s2){
    int i=0,min1=0,min2=0;
    for(i=0;i<n;++i)
        if(!HT[i].parent){
            min1=i;
            break;
        }
    for(i=0;i<n;++i)
        if(!HT[i].parent&&HT[i].weight<HT[min1].weight)
            min1=i;
    for(i=0;i<n;++i)
        if(!HT[i].parent&&i!=min1){
            min2=i;
            break;
        }
    for(i=0;i<n;++i)
        if(!HT[i].parent&&HT[i].weight<HT[min2].weight&&i!=min1)
            min2=i;
    s1=min1;
    s2=min2;
}

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC,long long int *w, int n){
    if (n<=1)
        return;
    long long int m=2*n-1,i=0,*weight=w;
    HT=new HTNode[m];
    HuffmanTree p=HT;
    for(i=0;i<n;++i,++p,++weight)
        *p={*weight,0,0,0};
    for(;i<m;++i,++p)
        *p={0,0,0,0};
    for(i=n;i<m;++i){
        int s1=0,s2=0;
        Select(HT,i,s1,s2);//找到i之前的权重最小且双亲为0的两个权重
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
    HT[m-1].parent=0;
    HC=new char*[n+1];
    char *cd=new char[n];
    cd[n-1]='\0';
    for(i=0;i<n;++i){
        int start=n-1;
        for(int c=i,f=HT[i].parent;f&&f<m;c=f,f=HT[f].parent)
            if(HT[f].lchild==c)
                cd[--start]='0';
            else
                cd[--start]='1';
        HC[i]=new char[n-start];
        strcpy(HC[i],&cd[start]);
        huffmanMap[i].character = character[i];
        huffmanMap[i].huffmanCode = HC[i];
        //cout<<huffmanMap[i-1].character<<" "<<huffmanMap[i-1].huffmanCode<<endl;
    }
    delete []cd;
}

void HuffmanDecoding(HuffmanTree HT, char *s,int length, int n){//s为编码后的字符串
    int i=2*n-2;//根节点
    char c[1000]="";
    for(int j=0;j<length;++j){
        if(s[j]=='0'){
            i=HT[i].lchild;
            int length=strlen(c);
            c[length]=s[j];
            c[length+1]='\0';
        }
        else{
            i=HT[i].rchild;
            int length=strlen(c);
            c[length]=s[j];
            c[length+1]='\0';
        }
        if(!HT[i].lchild&&!HT[i].rchild){
            for(int k=0; k<n; k++) {
                if(!strcmp(c, huffmanMap[k].huffmanCode)) {
                    cout<<huffmanMap[k].character;
                    break;
                }
            }
            c[0]='\0';
            i=2*n-2;
        }
    }
}

long long int w[56]={0};
void CountLetter(){
    char c;
    int i=0;
    FILE *fp=fopen("./huffman_test/1/1_2.txt","rb");
    if(!fp){
        fprintf(stderr,"无法打开文件\n");
        exit(0);
    }
    while((c=fgetc(fp))!=EOF){
        if(c>='a'&&c<='z')
            w[c-'a'+1]++;
        else if(c>='A'&&c<='Z')
            w[c-'A'+27]++;
        else if(c==' ')
            w[0]++;
        else if(c==',')
			w[53]++;
		else if(c=='.')
			w[54]++;
		else if(c=='\'')
			w[55]++;
    }
    fclose(fp);
}

char* readFile() {
    FILE* file = fopen("./huffman_test/2/2_1.txt", "rb");
    if (file == NULL) {
        printf("Failed to open file\n");
        return NULL;
    }
    fseek(file, 0, SEEK_END);// Move the cursor to the end of the file
    long filesize = ftell(file); // Get the current cursor position (which is the size of the file)
    fseek(file, 0, SEEK_SET);// Move the cursor back to the beginning of the file
    char* buffer = new char[filesize + 1];
    if (buffer == NULL) {
        printf("Failed to allocate memory\n");
        return NULL;
    }
    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';
    fclose(file);
    //cout<<buffer<<endl;
    return buffer;
}

void compressBinaryString(const char* binary, char* compressed, int length) {
    for(int i = 0; i < length; i += 8) {
        char temp = 0;
        for(int j = 0; j < 8; j++) 
            temp = (temp << 1) | (binary[i + j] - '0');
        compressed[i/8] = temp;
    }
    compressed[length/8] = '\0';
}

void decompressBinaryString(const char* compressed, char* decompressed, int length) {
    for (int i = 0; i < length; ++i) 
		for (int j = 7; j >= 0; --j) 
		    decompressed[i * 8 + (7 - j)] = ((compressed[i] >> j) & 1) + '0';
	decompressed[length * 8] = '\0';
}

int main(){
    //int n=0;
    //cin>>n;
    //int *w=new int[n];
    //for(int i=0;i<n;++i)
    //    cin>>w[i];
    CountLetter();
    //for(int i=0;i<53;++i)
    //    cout<<w[i]<<endl;
    HuffmanCoding(HT,HC,w,56);
    char code[10000]="", *s=readFile();
    cout<<s<<endl;
    while (*s){
        if (*s>='a'&&*s<='z'){
            strcat(code,HC[*s-'a'+1]);
            //cout<<*s<<" "<<code<<endl;
            }
        else if (*s>='A'&&*s<='Z'){
            strcat(code,HC[*s-'A'+27]);
            //cout<<*s<<" "<<code<<endl;
            }
        else if (*s==' '){
            strcat(code,HC[0]);
            //cout<<*s<<" "<<code<<endl;
            }
        else if(*s==',')
        	strcat(code,HC[53]);
        else if(*s=='.')
		    strcat(code,HC[54]);
		else if(*s=='\'')
			strcat(code,HC[55]);
        ++s;
    }
    //cout<<code<<endl;
    int lengthInit = strlen(code);
    int padding = 8 - (lengthInit % 8);
    for(int i = 0; i < padding; i++) 
        strcat(code, "0");
    int length1 = strlen(code);
   	//cout<<code<<endl;
    //cout<<lengthInit<<endl<<length1<<endl;
    char* compressed = new char[length1/8+1];
    compressBinaryString(code, compressed, length1);
    int i=0;
    //for(i=0;compressed[i]||(!compressed[i]&&compressed[i+1]);++i);
    int length2 =length1/8;
    cout<<length2<<endl;
    char* decompressed = new char[length2* 8 + 1];
    decompressBinaryString(compressed, decompressed, length2);
    cout<<"解压缩后："<<endl;
    HuffmanDecoding(HT,decompressed,lengthInit,56);
    for (int i = 0; i <= 56; ++i) 
       delete[] HC[i];
    delete[] HC;
    delete[] HT;
    delete[] compressed;
    delete[] decompressed;
    return 0;
}
