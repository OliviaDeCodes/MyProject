/*************************************************************************
	> File Name: client1.c
	> Author: 
	> Mail: 
	> Created Time: 二 12/18 20:43:09 2018
 ************************************************************************/
#include "./common.h"
#define num 1
#define MAX_SIZE 1024
#define INS 6

typedef struct script{
    char *name;
    char *path;
    int time, id;
} script;

script sc[INS];



int start_socket(int port) {
    int socket_server, sockfd;
    struct sockaddr_in s_addr;
    socklen_t len;

    if((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }


    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = htons(INADDR_ANY);

    int opt = 1;
    setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));

    if((bind(socket_server, (struct sockaddr*) &s_addr, sizeof(struct sockaddr))) < 0) {
        perror("bind");
        return -1;
    }

    if(listen(socket_server, num) < 0) {
        perror("listem");
        return -1;
    }
    return socket_server;
}

//心跳机制
int heart(int port, char*IP) {
    int socketfd;
    struct sockaddr_in dest_addr;

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error\n");
        return -1;
   }

    //设置服务器
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);//本地字节序转化为网络字节序
    dest_addr.sin_addr.s_addr = inet_addr(IP);//点跟十进制，转化为数值给这个地址

    //链接服务器
    if (connect(socketfd, (struct sockaddr *)&dest_addr,sizeof(struct sockaddr)) == -1) {
        perror("Connect");
        close(socketfd);
        return -1;
    }

    close(socketfd);
    return 0;
}

char * get_conf_value(const char *pathname, const char *key_name){
    char *line;
    size_t len = 0;
    ssize_t read;
    char *value = (char *)calloc(sizeof(char), 100);
    FILE *fp = NULL;
    fp = fopen(pathname, "r");
    if (fp == NULL) {
        perror("fopen:");
        return NULL;
            
    }

    while ((read = getline(&line,&len,fp)) > 0) {
        char *ptr = strstr(line,key_name);
        if (ptr == NULL) continue;
        ptr += strlen(key_name);
        if (*ptr != '=') continue;
        strncpy(value, (ptr+1), strlen(ptr+2));//strlen(per+2) 少获取一个长度，代表换行
        int tempvalue = strlen(value);
        value[tempvalue] = '\0';
            
    }
        fclose(fp);
        return value;

}


pthread_mutex_t mutex[INS + 1];
void pthread_init(){
    for (int i = 0; i < INS; i++) {
        pthread_mutex_init(&mutex[i], NULL);
    }
}



int init_script(script *sc) {
    sc[0].name = get_conf_value("./client.conf", "name0");
    sc[0].path = get_conf_value("./client.conf", "path0");
    sc[0].time = atoi(get_conf_value("./client.conf", "time0"));
    sc[0].id = 0;

    sc[1].name = get_conf_value("./client.conf", "name1");
    sc[1].path = get_conf_value("./client.conf", "path1");
    sc[1].time = atoi(get_conf_value("./client.conf", "time1"));
    sc[1].id = 1;

    sc[2].name = get_conf_value("./client.conf", "name2");
    sc[2].path = get_conf_value("./client.conf", "path2");
    sc[2].time = atoi(get_conf_value("./client.conf", "time2"));
    sc[2].id = 2;

    sc[3].name = get_conf_value("./client.conf", "name3");
    sc[3].path = get_conf_value("./client.conf", "path3");
    sc[3].time = atoi(get_conf_value("./client.conf", "time3"));
    sc[3].id = 3;

    sc[4].name = get_conf_value("./client.conf", "name4");
    sc[4].path = get_conf_value("./client.conf", "path4");
    sc[4].time = atoi(get_conf_value("./client.conf", "time4"));
    sc[4].id = 4;
    
    sc[5].name = get_conf_value("./client.conf", "name5");
    sc[5].path = get_conf_value("./client.conf", "path5");
    sc[5].time = atoi(get_conf_value("./client.conf", "time5"));
    sc[5].id = 5;

    return 0;
}

//检查警告信息,检查到主动连接master
void warning(char *buff, int id) {
    if (id > 2) return;
    if (id != 0 && strstr(buff, "warning") == NULL) return;
    if (id == 0 && strlen(buff) == 0) return;
    printf("***<< 有警告信息 准备连接 >>***\n");
    struct sockaddr_in w_addr;
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(0);
    }

    char value1[20];
    char *host = get_conf_value("./client.conf", "IP");

    w_addr.sin_family = AF_INET;
    w_addr.sin_port = htons(1996);
    w_addr.sin_addr.s_addr =inet_addr(host);

    if (connect(sockfd, (struct sockaddr *) &w_addr, sizeof(struct sockaddr)) < 0){
        perror("warnning memset connect:");
        close(sockfd);
        return;
    } 
    printf("==>警告连接 连接成功<==\n");
    send(sockfd, buff, strlen(buff), 0);
    printf("==> 成功传送信息:%s \n", buff);
    close(sockfd);

}

void *func(void *arg);
void *func1(void *arg);

int main() {

    char *host = get_conf_value("./client.conf", "IP");
    int port = atoi(get_conf_value("./client.conf", "master_port"));
    printf("%d %s\n", port, host);
    init_script(sc);
    pthread_init();
    pthread_t t[INS + 2];

    //创建一个线程，6个线程
    for (int i = 0; i < INS; i++) {
        if (pthread_create(&(t[i]), NULL, func, (void *)&sc[i]) == -1) {
            perror("pthread_create_func:\n");
            return -1;
        }
    }
    
    if (pthread_create(&(t[6]), NULL, func1, NULL) == -1) {
        perror("pthread_create_func1:\n");
        return -1;
    }

    //主线程心跳连接
    while(1) {
        heart(port, host);
        sleep(15);
    }
    for (int i = 0; i <= 20; i++) {
        pthread_join(t[i], NULL); //等待当前执行的线程完毕
    }
    return 0;
}

void *func(void *arg) {
    script *te = (script *)arg;
    pthread_init();
    while(1) {
        pthread_mutex_lock(&mutex[te->id]);
        FILE *fp = popen(te->path, "r");
        printf("%d\n", te->id);
        printf("%s\n", te->path);
        printf("%d (s)\n", te->time);
        char buff[MAX_SIZE];
        memset(buff, 0, sizeof(buff));
        char dirname[MAX_SIZE] = "./";
        strcat(dirname, te->name);
        strcat(dirname, ".log");
        printf("准备存入\n");
        fread(buff, sizeof(char), MAX_SIZE, fp);
        printf("%s\n", buff);
        printf("%s\n", dirname);
        //检查是否有警告信息，此处调用一个警告函数
        warning(buff, te->id);
        FILE *fl = fopen(dirname, "at+");
        fwrite(buff, sizeof(char), strlen(buff), fl);
        pthread_mutex_unlock(&mutex[te->id]);
        pclose(fp);
        fclose(fl);
        sleep(sc->time);
    }
    exit(0);
}

void *func1(void *arg) {
    int socket_server = start_socket(9011);
    int sock_server = start_socket(2002);
    while(1){
        signal(SIGPIPE, SIG_IGN);
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        int coon;
        if ((coon = accept(socket_server, (struct sockaddr *) &client_addr, &len)) < 0) {
            perror("accept");
            close(coon);
            continue;
        } else {
            printf("accept %d ok\n", socket_server);
        }
        int newfd, id;
        int renum;
        FILE *fp;
        char buffer[MAX_SIZE + 1] = {0};
    
        for (renum = 100; renum <= 105; renum++) {
            if(send(coon, &renum, 4, 0) <= 0) {
                perror("send error:");
                break;
            }
            if(recv(coon, &id, MAX_SIZE, 0) <= 0) {
                perror("send error:");
                break;
            }
            printf("%d\n", id);
            struct sockaddr_in c_addr;
            socklen_t len2 = sizeof(c_addr);
            if ((newfd = accept(sock_server, (struct sockaddr *) &c_addr, &len2)) < 0) {
                perror("accept");
                close(newfd);
                break;
            } 

            printf("Connect succes!\n");
            pthread_mutex_lock(&mutex[id%10]);
            //打开文件
            if(id == 101) {
                fp = fopen("./cpu.log", "r");
            } else if(id == 105) {
                fp = fopen("./disk.log", "r");
            } else if(id == 104) {
                fp = fopen("./mem.log", "r");
            } else if(id == 103) {
                fp = fopen("./user.log", "r");
            } else if(id == 102) {
                fp = fopen("./system.log", "r");
            } else if(id == 100) {
                fp = fopen("./malicious_process.log", "r");
            }

			while (fread(buffer, 1, MAX_SIZE, fp) > 0) {
                buffer[MAX_SIZE] = '\0';
                send(newfd, buffer, strlen(buffer), 0); 
                printf("data:%s",buffer);
                printf("*** 传完文件，准备删除 ***\n");
                if (id == 101) {
                    system(" > ./cpu.log");
                }else if (id == 105) {
                    system(" > ./disk.log");
                }else if (id == 104) {
                    system(" > ./mem.log");
                }else if (id == 103) {
                    system(" > ./user.log");
                }else if (id == 102) {
                    system(" > ./system.log");
                }else if (id == 100) {
                    system(" > ./malicious_process.log");
                }
                memset(buffer, 0, sizeof(buffer));
            }
            pthread_mutex_unlock(&mutex[id%10]);
            fclose(fp);
            close(newfd);
        }
    
        close(coon);
        sleep(3);
    }
    
    close(socket_server);
}

