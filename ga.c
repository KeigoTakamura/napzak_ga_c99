//#include<iostream>
#include<stdlib.h>
//#include<vector>
#include<time.h>
#include<stdio.h>

#define objc_max 4  //オブジェクトの個数
#define ga_mon 9 //個体数
#define zac_max 9  //ザックの最大容量
#define max 200
#define ga_rank  10 //遺伝子の世代

 int num_val[objc_max]={4,5,12,14};//オブジェクトの価値
 int num_obj[objc_max]={2,3,5,6};//オブジェクトの重量 //constだと色々めんどくさいため



struct  ga_ss{ //評価要素構造体
    int sum_c;//合計重量
    int sum_v;//合計価値
    int gas[objc_max];//遺伝子染色体
}typedef ga_s;




int ga_sumV(ga_s *ga_arr){//オブジェクトの総価値計算関数
    int sums=0;

    for (int i = 0; i < ga_mon; i++)
    {
        sums += ga_arr[i].sum_v;
    }
    
    
    return sums;//総価値
}


ga_s Eva(ga_s ga){//評価値算出
    ga.sum_c=0;
    ga.sum_v=0;
    for(int i=0; i  <  objc_max ; i++ ){
        ga.sum_c = ga.sum_c *num_val[i];  //ここで重量計算
    }

    if(ga.sum_c > zac_max){
        ga.sum_v = 0;//重さがオーバーしたらゼロ
    }else{
        for(int t=0;t < objc_max ; t++){
            ga.sum_v  =  num_val[t] +ga.sum_v; //オーバーしてなかったら価値をそのまま適合度（評価値）として代入
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
    //std ::vector<int> num_value{4,5,12,14};//商品の価値
    //std ::vector<int> num_obj{2,3,5,6}; //商品の重量  
    //std ::vector <vector<bool>>(objc_max, gas(4,0));  //遺伝子
    int sums=0; //いらないかも
    float P=0.0;//ルーレット選択確率

    //int num_ga [ga_mon][objc_max];//遺伝子の皆さん
    //int Eva_ans[objc_max];//評価値
    ga_s num_gas[ga_mon];//ナップザック構造体配列宣言
    int one=0,cnt1=-1;//上位一位遺伝子
    int two=0,cnt2=-1;//上位二位遺伝子
    
    srand(time(NULL));

    ga_s one_gas;
    ga_s two_gas;

    

    for(int i=0;i< ga_mon ;i++){
        for(int t=0;t < objc_max;t++){
            num_gas[i].gas[t]=rand()%2;//遺伝子生成
        }
    }
    
    for(int gen=0; gen < ga_rank; gen++){ //世代の数だけ繰り返す
         //遺伝子評価フェーズ
            for(int Eva_count=0 ; Eva_count < ga_mon;Eva_count++){//遺伝子の数だけ繰り返したりする
                num_gas[Eva_count]  = Eva(num_gas[Eva_count]);//評価関数
            }
        //上位遺伝子決定フェーズ
            for (int i = 0; i < ga_mon; i++) //上位1位の染色体を抽出
            {
                if(num_gas[i].sum_v  > cnt1  ){
                    one =i;//一番上位の遺伝子番号を登録
                    cnt1 = num_gas[i].sum_v;
                }
            }
            
            for (int i = 0; i < ga_mon; i++)//上位二位の染色体を抽出
            {
                if (num_gas[i].sum_v > cnt2 && i != one)//一番上位の遺伝子を除く
                {
                    two=i;//二番目に上位の遺伝子を上書き
                    cnt2=num_gas[i].sum_v; //値を
                }
            }

            //エリート個体保存フェーズ
            one_gas = num_gas[one];//一番上位の個体を保存
            two_gas = num_gas[two];//二番目に上位の個体を保存

            //ルーレット選択フェーズ
            //ob_sumが価値の合計値になる

            sums = ga_sumV(num_gas);//染色体総価値の計算
            for (int ob = 0; ob < ga_mon ; ob++)
            {   
                
                
            }
            

            
            

           
            

            
        }

    
