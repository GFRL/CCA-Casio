# CCA-Casio
 

# MTCSCCA
Goal：拆分成两个文件，实现完整版

## 宏定义
maxn: 无用
MTCSXS:MTCS算法的参数
typenum:所有动作的数量（请完善以下列表）
动作编号  动作


maxjs：角色数量 (注意，编号由0开始)暂时只能是2
shichang: AI思考的时间
COUNT：AI运行次数

## 类定义

### Action

from,to,type包括来自谁？，攻击谁？还有动作类型（各种子弹血量等消耗我暂时用Q，Qb,Qs,Qv等map实现，可直接删除）


### Game
{
    num--人数
    next_sword是剩余剑数
    now_action存储两个角色的选择
}
Get_allowed_action(int u) 返回一个vector，里面是角色u在目前局面下的合法选择对应的编号
void step(int real=0)根据now_action 更新其他数据，real=0表示训练，无需任何屏幕输出，real=1可以输出点啥，用于测试效果
output(int js)这只是输出提示语
end()返回游戏是否结束，结束为true
get_value(int js,int type)返回当前局面下对js来说的局面评判函数，type是采用哪一种办法评判，这样子可以进行多种估值函数的比较，
tmp_value(int js,int type)是用来实现get_value的，可以删去，也可保留

### cjd
貌似没啥需要关心的