struct conn{
    int id;
};

struct data{
    int cliente;
    char buffer[1024];
};

struct packet{
    int tipo;
    union {
        struct conn conn;
        struct data data;
    };
};

enum {ePKT_CONN,ePKT_DATA,ePKT_RESULT};
struct PKT_CONN{
	int id_cliente;
	char nombre[10];
};
struct PKT_DATA{
	int id_cliente;
	int precio;
	char producto[50];
};
struct PKT_RESULT{
	int id_win;
};
struct PKT{
	int tipo; 
	union {struct PKT_DATA data;struct PKT_CONN conn;struct PKT_RESULT result;};
};


