//
// Created by Tahir Iqbal on 12.12.24.
//
#include "pigeon.h"

bool sendmail(Email *email, const Server *server) {
    int8 buffer[256];
    struct sockaddr_in sock;
    int16 s;
    email->state++;
    signed int tmp = socket(AF_INET, SOCK_STREAM, 0);
    assert(tmp > 0);
    s = (int16) tmp;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(25);
    sock.sin_addr.s_addr = server->ip;
    tmp = connect($i s, (struct sockaddr *) &sock, sizeof(struct sockaddr));
    assert(!tmp);
    email->state++;
    log("connected to %s\n", $c server->server);

    zero(buffer, 256);
    tmp = read($i s, $c buffer, 255);
    dprintf($i s, "EHLO %s\n", $c email->domain);

    zero(buffer, 256);
    tmp = read($i s, $c buffer, 255);
    log("from server: '%s'\n", $c buffer);
    close(s);
    return true;
}

int main(int argc, char *argv[]) {

    Email *e = malloc(sizeof(struct s_email));
    zero($1 e, sizeof(struct s_email));
    Server *s = malloc(sizeof(struct s_server));
    zero($1 s, sizeof(struct s_server));

    e->state = idle;
    strncpy($c e->src, $c "tahir@test.com", 63);
    e->domain = e->src + 6;

    strncpy($c s->server, $c "mail_cluster.loopia.se", 63);
    s->ip = inet_addr("93.188.3.12");
    bool result = sendmail(e, s);
    log("%d\n", result);
    free(s);
    free(e);
    return 0;
}
