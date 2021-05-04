filename='student.txt'
import os   #导入磁盘模块
def main():
    while True:
        menu()
        choice = int(input('请选择'))
        if choice in[0, 1, 2, 3, 4, 5, 6, 7]:
            if choice == 0:
                answer = input('你确定要退出系统吗？y/n')
                if answer == 'y' or answer == 'Y':
                    print('感谢你的使用')
                    break
                else:
                    continue
            elif choice == 1:
                insert()
            elif choice == 2:
                search()
            elif choice == 3:
                delete()
            elif choice == 4:
                modify()
            elif choice == 5:
                sort()
            elif choice == 6:
                total()
            elif choice == 7:
                show()

def menu():
    print('=================学生信息管理系统================')
    print('-----------------功能菜单-----------------------')
    print('1.录入学生信息')
    print('2.查找学生信息')
    print('3.删除学生信息')
    print('4.修改学生信息')
    print('5.排序')
    print('6.统计学生信息')
    print('7.显示所有学生信息')
    print('0.退出')

def insert():
    student_list = []  # 存储学生信息
    while True:
        id = input('请输入ID（如1001）')
        if not id:  # 若输入的id为空
            break
        name = input('请输入姓名')
        if not name:
                break


        try:
            english = int(input('请输入英语成绩'))
            python = int(input('请输入python成绩'))
            java = int(input('请输入java成绩'))
        except:
            print('输入无效，不是整数类型，请重新输入')
            continue    # 使程序再次运行
        #将录入的学生信息保存到字典中
        student = {'id':id, 'name': name, 'english':english, 'python':python, 'java':java}  #注意这个括号
        #将学生信息添加到列表中
        student_list.append(student)
        answer=input('是否继续添加?y/n\n')
        if answer=='y':
            continue
        else:
            break

    #调用save()函数
    save(student_list)
    print('学生信息录入完毕')

def save(lst):
    try:
        stu_txt=open(filename,'a',encoding='utf-8') # a是以追加模式打开，encoding是为了防止中文乱码
    except:
        stu_txt=open(filename,'w',encoding='utf-8') # w是以写的方式打开，若上一步无文件以追加模式打开
                                                    # 会出错，所以在空文件的情况用写入模式
    for item in lst:
        stu_txt.write(str(item)+'\n')   # 将stu_txt逐个写入文件内
    stu_txt.close()

def search():
    student_query=[]    # 定义一个列表，因为可能有重名，所以不用字典
    while True:
        id=''
        name=''     # 这两个估计不用先定义
        if os.path.exists(filename):
            mode=input('按id查找请输入1，按姓名查找请输入2')
            if mode=='1':   # input默认的类型为str，所以这里的1要加引号
                id=input('请输入学生id')
            elif mode=='2':
                name=input('请输入学生姓名')
            else:
                print('你的输入有误，请重新输入')
                search()    # 估计也可以用continue,还避免了陷入循环
            with open(filename,'r',encoding='utf-8') as rfile:
                student=rfile.readlines()
                for item in student:
                    d=dict(eval(item))
                    if id!='':
                        if d['id']==id:
                            student_query.append(d)
                    elif name!='':
                        if d['name']==name:
                            student_query.append(d)
            # 显示查询结果
            show_student(student_query)
            # 清空列表
            student_query.clear()   # clear是自带的清空函数
            answer=input('是否要继续查询?y/n\n')
            if answer=='y':
                continue
            else:
                break
        else:
            print('该文件不存在')
            return  # break适合结束循环，return结束函数

def show_student(lst):
    if len(lst)==0: # 列表长度为0，即无数据
        print('没有查询到学生信息，无数据显示\n')
        return
    # 定义标题显示格式,有点复杂，可以调试慢慢看
    format_title='{:^6}\t{:^12}\t{:^8}\t{:^10}\t{:^10}\t{:^8}'

    #format() 函数与数字，字符结合使用
    #^, <, > 分别是居中、左对齐、右对齐，后面带宽度，
    #: 号后面带填充的字符，只能是一个字符，不指定则默认是用空格填充。
    #+ 表示在正数前显示 +，负数前显示 -；  （空格）表示在正数前加空格
    #b、d、o、x 分别是二进制、十进制、八进制、十六进制。

    print(format_title.format('ID','姓名','英语成绩','python成绩','java成绩','总成绩'))
    #定义内容的显示格式
    format_data='{:^6}\t{:^12}\t{:^8}\t{:^10}\t{:^10}\t{:^8}'   # 为了显示的两行可以随意调整间隔，不然用
                                                                # 上面的format_title也可以
    for item in lst:
        print(format_data.format(item.get('id'),
                                 item.get('name'),
                                 item.get('english'),
                                 item.get('python'),
                                 item.get('java'),
                                 int(item.get('english'))+int(item.get('python'))+int(item.get('java'))
                                 ))   # 第二个format是函数，get函数是通过键取字典里的值

def delete():
    while True:
        student_id=input('请输入你要删除的学生的ID')
        if student_id!='':  # 输入的id不为空,为空的话就直接重复循环了
            if os.path.exists(filename):    # 判断文件是否存在磁盘中，os为磁盘
                with open(filename,'r',encoding='utf-8')as file:
                    student_old=file.readlines()    # readlines()一次性读取整个文件内容，且将我们的内
                                                    # 容都放进一个list列表中，连空格和\n都保留了下来
            else:
                student_old=[]  # 若文件不存在则令student_old为空
            flag=False  # 标记是否删除
            if student_old: # 列表student_old不为空才可以运行
                with open(filename,'w',encoding='utf-8')as wfile:
                    d={}    # 定义一个空字典
                    for item in student_old:
                        d=dict(eval(item))  # eval将字符串转换为字典,dict是创建一个字典
                        if d['id']!=student_id: # 输入的学生id不在字典内
                            wfile.write(str(d)+'\n')    # 将字典内信息以字符串格式写回文件,w是覆盖式的写，所以要重新写回去
                            print('hello world')
                        else:
                            flag=True   # 表示已经删除，不写回文件就相当于删除
                    if flag:    # 因为True为1
                        print(f'id为{student_id}的学生信息已被删除')
                    else:
                        print(f'没有找到id为{student_id}的学生信息')
            else:   # 即filename文件是空文件则运行此步
                print('文件内无学生信息')  # 因为空文件里面没有信息
                break
            show()  # 删除后要重新显示所有学生信息,这是另外一个函数
            answer=input('是否继续删除?y/n\n')
            if answer=='y':
                continue
            else:
                break

def modify():
    show()
    if os.path.exists(filename):
        with open(filename,'r',encoding='utf-8') as rfile:
            student_old=rfile.readlines()
    else:
        print("没有这个文件")
        return
    student_id=input('请输入你要修改的学生id')
    with open(filename,'w',encoding='utf-8') as wfile:
        for item in student_old:
            d=dict(eval(item))  # 字符串转化为字典
            if d['id']==student_id:
                print('可以修改此学生信息')
                while True:
                    try:
                        d['name']=input('请输入姓名')
                        d['english']=input('请输入英语成绩')
                        d['python']=input('请输入python成绩')
                        d['java']=input('请输入java成绩')
                    except:     #这是出现异常时运行的
                        print('输入有误，请重新输入')
                    else:
                        break   # break只能在循环中使用
                wfile.write(str(d)+'\n')
                print('修改成功')
            else:
                wfile.write(str(d)+'\n')    # 覆盖式打开文件，所以要一直写入
        answer=input('是否继续修改其他学生信息:y/n\n')
        if answer=='y':
            modify()    # continue是终止后面的语句，重新循环，但这里没有循环，所以用递归调用


def sort():
    show()
    if os.path.exists(filename):
        with open(filename,'r',encoding='utf-8') as rfile:
            student_list=rfile.readlines()
        student_new=[]
        for item in student_list:
            d=dict(eval(item))
            student_new.append(d)
    else:
        return
    asc_or_desc=input('请选择(0,升序 1，降序)')
    if asc_or_desc=='0':
        asc_or_desc_bool=False
    elif asc_or_desc=='1':
        asc_or_desc_bool=True
    else:
        print('你的输入有误，请重新输入')
        sort()
    mode=input('请选择排序方式（1.按英语成绩排序 2.按python成绩排序 3.按Java成绩排序 0.按总成绩排序')
    if mode=='1':
        student_new.sort(key=lambda student_new:int(student_new['english']),reverse=asc_or_desc_bool)
        #上面那个sort是系统自带的函数，里面填（self:key,reverse),self为传进去的函数，key为目标，reverse为排序方式
        #主要有False和True，这个在上面赋值过了，lambda为匿名函数：是指一类无需定义标识符（函数名）的函数或子程序。
        #因为开头是student_new.sort，所以self可以为student_new不用定义，对于key=lambda student: student.age要为
        #这种格式，注意那个冒号
    elif mode=='2':
        student_new.sort(key=lambda student_new:int(student_new['python']),reverse=asc_or_desc_bool)
    elif mode=='3':
        student_new.sort(key=lambda student_new,:int(student_new['java']), reverse=asc_or_desc_bool)
    elif mode=='0':
        student_new.sort(key=lambda student_new:int(student_new['english'])
                                                   +int(student_new['english'])
                                                   +int(student_new['english'])
                         ,reverse=asc_or_desc_bool)
        # 不是打印的情况下代码似乎可以随意换行
    else:
        print('你的输入有误a，请重新输入')
        sort()
    show_student(student_new)


def total():
    if os.path.exists(filename):
        with open(filename,'r',encoding='utf-8') as rfile:
            student=rfile.readlines()
            if student:
                print(f'一共有{len(student)}名学生\n')
            else:
                print('还没有录入学生成绩')
    else:
        print('文件不存在')

def show():
    student_lst=[]  # 创建一个空列表
    if os.path.exists(filename):
        with open(filename,'r',encoding='utf-8') as rfile:
            student=rfile.readlines()   # readlines的读取是字符串类型
            for item in student:
                student_lst.append(eval(item))  # eval是为了将字符串转为列表
                                                #一、字符串转换成列表
                                                #二、字符串转换成字典
                                                #三、字符串转换成元组
            if student_lst:
                show_student(student_lst)   # show_student是另外一个函数,主要用于格式问题
    else:
        print('该文件不存在')


if __name__ == '__main__':  # 这句是程序运行代码，背吧
    main()