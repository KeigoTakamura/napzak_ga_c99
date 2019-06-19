//#include<iostream>
#include<stdlib.h>
//#include<vector>
#include<time.h>
#include<stdio.h>

#define objc_max 10  //オブジェクトの個数 アイテム数
#define ga_mon 90 //個体数
#define zac_max 450  //ザックの最大容量
#define max 200
#define ga_rank  1000//遺伝子の世代
#define late_a 50  
#define random_late 15  //突然変異

int num_val[objc_max]={4,5,12,14,11,3,8,10,9,19};//オブジェクトの価値
int num_obj[objc_max]={2,3,5,6,3,9,12,1,10,20};//オブジェクトの重量 //constだと色々めんどくさいため

struct  ga_ss{ //評価要素構造体
    int sum_c;//合計重量
    int sum_v;//合計価値
    int gas[objc_max];//遺伝子染色体
}typedef ga_s;

int ga_sumV(ga_s *ga_arr){//オブジェクトの総価値計算関数
    int sums=0;

    for (int i = 0; i < ga_mon; i++)
    {
        sums = sums+ ga_arr[i].sum_v;
    }
    return sums;//総価値
}

int obj_sum_val(){
    int sum=0;
    for(int i=0;i<objc_max;i++)
        sum+=num_val[i];
    return sum;
}

ga_s Eva(ga_s ga){//評価値算出
    ga.sum_c=0;
    ga.sum_v=0;
    for(int i=0; i  <  objc_max ; i++ ){
        ga.sum_c +=  ga.gas[i] * num_obj[i];  //ここで重量計算
    }

    if(ga.sum_c > zac_max){
        ga.sum_v = 0;//重さがオーバーしたらゼロ
    }else{
        for(int t=0;t < objc_max ; t++){
            ga.sum_v  =  num_val[t]*ga.gas[t] +ga.sum_v; //オーバーしてなかったら価値をそのまま適合度（評価値）として代入
        }
    }
return  ga;   
}

//コーディングメモ
/*
美しくするなら商品価値と商品の重量こそ構造体で記述するなりしたほうがよかった
理想はC++でGA Classを作ってvectorとboolで染色体を実装したい

・Eva(ga_s *ga) gaは遺伝子の染色体
*/

int main(){
    int logs[ga_rank];
    //std ::vector<int> num_value{4,5,12,14};//商品の価値
    //std ::vector<int> num_obj{2,3,5,6}; //商品の重量  
    //std ::vector <vector<bool>>(objc_max, gas(4,0));  //遺伝子
    float frand =(float)RAND_MAX;//乱数範囲をfloatで指定
    int sums=0; //総価値の合計
    int epw=0;//答えが収束したら強制終了させるための変数
    int r1=0,r2=0;//二点交叉の交叉範囲ne
    int sum_vs=0;//ルーレット用加算値
    int arr=0;//ルーレット選択確率_整数
    //int num_ga [ga_mon][objc_max];//遺伝子の皆さん
    //int Eva_ans[objc_max];//評価値
    ga_s num_gas[ga_mon];//ナップザック構造体配列宣言
    ga_s num_child[2]; //交叉遺伝子
    ga_s sub_ga;//次世代遺伝子のいでモノ　
    int one=0,cnt1=0;//上位一位遺伝子
    int two=0,cnt2=0;//上位二位遺伝子
    
    srand(time(NULL));

    ga_s one_gas;//エリート遺伝子
    ga_s two_gas;//エリート遺伝子

    sums = obj_sum_val();//荷物の総価値の計0

    for(int i=0;i< ga_mon ;i++){
        for(int t=0;t < objc_max;t++){
            num_gas[i].gas[t]=rand()%2;//遺伝子生成
        }
    }
    


    for(int gen=0; gen < ga_rank; gen++){ //世代の数だけ繰り返す
            one=0,two=0;//エリート初期化
         //遺伝子評価フェーズ
            for(int Eva_count=0 ; Eva_count < ga_mon;Eva_count++){//遺伝子の数だけ繰り返したりする
                num_gas[Eva_count]  = Eva(num_gas[Eva_count]);//評価関数　.sun_vに評価値を入れる。
            }
        //上位遺伝子決定フェーズ
            for (int i = 0; i < ga_mon; i++) //上位1位の染色体を抽出
            {
                if(num_gas[i].sum_v  > cnt1  ){
                    one =i;//一番上位の遺伝子番号を登録
                    cnt1 = num_gas[i].sum_v;//最大価値を保存
                }
            }
            
            logs[gen] = cnt1;

            for (int i = 0; i < ga_mon; i++)//上位二位の染色体を抽出
            {
                if (num_gas[i].sum_v > cnt2 && i != one)//一番上位の遺伝子を除く
                {
                    two=i;//二番目に上位の遺伝子を上書き
                    cnt2=num_gas[i].sum_v; //二番目に大きい価値を保存
                }
            }

            //エリート個体保存フェーズ
            one_gas = num_gas[one];//一番上位の個体を保存
            two_gas = num_gas[two];//二番目に上位の個体を保存
            
            //ルーレット選択フェーズ
            //ob_sumが価値の合計値になる

          
            for (int ob = 0; ob < ga_mon ; ob++)//ルーレットを遺伝子の個体数だけ回す
            {   
              //    P =(((float)num_gas[ob].sum_v / sums)*(float)rand()/rand());//選択確率＝P　　P= （染色体をごとの総価値÷総価値）＊ (0から1までの乱数)
                 
                arr = (int)((rand()/frand)*sums);//ルーレット
                
                for (size_t i = 0; i < ga_mon; i++)
                {
                    sum_vs+=num_gas[i].sum_v;//ルーレットに加算
                    if(sum_vs > arr){
                            sub_ga = num_gas[i];//ルーレット選択用に代入
                            break;//ルーレット選択終了
                    }
                }
            }
           //todo オブジェクトの個数と遺伝子の数がごっちゃになっているので修正する
            for (size_t i = 0; (objc_max%2 ==1 && i < objc_max-1)||(objc_max%2==0 &&i < objc_max-2) ; i++)//遺伝子交叉
            {//個体個数が奇数子の時個体数-1で終了、偶数子の時個体数-2で終了    
                arr = (int)((rand()/frand)*100);//交叉確率算出
                    
                if(arr > late_a){
                    r1 = (int)((rand()/frand)*(objc_max)); //objc_maxは遺伝子長
                    r2 = r1 + (int)((rand()/frand)*(objc_max-r1));
                    
                    for (int cout=0;cout < objc_max ; cout++){//二点交叉
                        if(r1 <=cout && cout<=r2){
                            num_child[0].gas[cout] = one_gas.gas[cout];
                            num_child[1].gas[cout] = two_gas.gas[cout];   
                        }else
                        {
                            num_child[0].gas[cout] = two_gas.gas[cout];
                            num_child[1].gas[cout] = one_gas.gas[cout];  
                        }
                    }
                    
                    one_gas = num_child[0];
                    two_gas = num_child[1];
                }
            }

            //突然変異

            for (int obj = 0; obj < ga_mon; obj++)
            {
                arr = (int)((rand()/frand)*100);
                
                if (arr > random_late) 
                {
                    r1  = (int)(rand()/frand)*(objc_max-1);
                    num_gas[obj].gas[r1] =  (num_gas[obj].gas[r1]+1)%2;//必要であれば遺伝子を入れ替えする
                 }
            }
            //エリート選択で使った遺伝子を元に戻す
            num_gas[one] = one_gas;
            num_gas[two] = two_gas;
        }
    
    for (size_t i = 0; i < ga_mon; i++)
    {
         num_gas[i]=Eva(num_gas[i]);
    }
    
    cnt1=0;
    for (int i = 0; i < ga_mon; i++) //上位1位の染色体を抽出
     {
                if(num_gas[i].sum_v  > cnt1  ){
                    one =i;//一番上位の遺伝子番号を登録
                    cnt1 = num_gas[i].sum_v;//最大価値を保存
                }
    }
   
    FILE *fp;
    fp=fopen("test.txt","w+");
    for(int j=0;j<ga_mon;j++){
        fprintf(fp,"%d %d \n",j,logs[j]);
    }
    fclose(fp);
    

    printf("output result %d %d\n",num_gas[one].sum_v,num_gas[one].sum_c);        
    printf("cnt %d \n",one);
    //ここにリザルトを出力する。
    return 0;
}
   
