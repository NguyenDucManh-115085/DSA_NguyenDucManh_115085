#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char hoten[30];
    int masv;
    float d1, d2, d3;
} Data;

typedef struct tagNode {
    Data infor;
    struct tagNode *link;
} Node;

typedef struct {
    Node *pHead;
    Node *pTail;
    int spt;
} LList;

void initList(LList *L) {
    L->pHead = NULL;
    L->pTail = NULL;
    L->spt = 0;
}

int emptyList(LList L) {
    return (L.spt == 0);
}
 
Node* createNode(Data x) {
    Node *pp = (Node*)malloc(sizeof(Node));
    if (pp != NULL) {
        pp->infor = x;
        pp->link = NULL;
    }
    return pp;
}

void insert_Head(LList *L, Data x) {
    Node *pp = createNode(x);
    if (pp == NULL) return;

    if (emptyList(*L)) {
        L->pHead = pp;
        L->pTail = pp;
    } else {
        pp->link = L->pHead;
        L->pHead = pp;
    }
    L->spt++;
}

void insert_Tail(LList *L, Data x) {
    Node *pp = createNode(x);
    if (pp == NULL) return;

    if (emptyList(*L)) {
        L->pHead = pp;
        L->pTail = pp;
    } else {
        L->pTail->link = pp;
        L->pTail = pp;
    }
    L->spt++;
}

Node* searchByID(LList L, int masv) {
    Node *p = L.pHead;
    while (p != NULL) {
        if (p->infor.masv == masv) {
            return p;
        }
        p = p->link;
    }
    return NULL;
}

void insert_After(LList *L, Node *q, Data x) {
    if (q == NULL) {
        printf("Khong tim thay nut goc de chen sau!\n");
        return;
    }
    Node *pp = createNode(x);
    if (pp == NULL) return;

    pp->link = q->link;
    q->link = pp;
    if (q == L->pTail) {
        L->pTail = pp;
    }
    L->spt++;
}

int delete_ByID(LList *L, int masv) {
    if (emptyList(*L)) return 0;

    Node *p = L->pHead;
    Node *prev = NULL;

    while (p != NULL && p->infor.masv != masv) {
        prev = p;
        p = p->link;
    }

    if (p == NULL) return 0;

    if (prev == NULL) {
        L->pHead = p->link;
        if (L->pHead == NULL) {
            L->pTail = NULL;
        }
    } else {
        prev->link = p->link;
        if (p == L->pTail) {
            L->pTail = prev;
        }
    }
    free(p);
    L->spt--;
    return 1;
}

void delete_Head(LList *L) {
    if (emptyList(*L)) {
        printf("Danh sach rong!\n");
        return;
    }
    Node *p = L->pHead;
    L->pHead = L->pHead->link;
    if (L->pHead == NULL) {
        L->pTail = NULL;
    }
    free(p);
    L->spt--;
    printf("Da xoa sinh vien dau danh sach.\n");
}

void delete_Tail(LList *L) {
    if (emptyList(*L)) {
        printf("Danh sach rong!\n");
        return;
    }
    if (L->pHead == L->pTail) {
        free(L->pHead);
        initList(L);
    } else {
        Node *p = L->pHead;
        while (p->link != L->pTail) {
            p = p->link;
        }
        free(L->pTail);
        L->pTail = p;
        L->pTail->link = NULL;
        L->spt--;
    }
    printf("Da xoa sinh vien cuoi danh sach.\n");
}

void sort_ByID(LList *L) {
    if (L->spt < 2) return;
    for (Node *i = L->pHead; i != NULL; i = i->link) {
        for (Node *j = i->link; j != NULL; j = j->link) {
            if (i->infor.masv > j->infor.masv) {
                Data temp = i->infor;
                i->infor = j->infor;
                j->infor = temp;
            }
        }
    }
    printf("Da sap xep danh sach tang dan theo Ma SV.\n");
}

void clearList(LList *L) {
    Node *p;
    while (L->pHead != NULL) {
        p = L->pHead;
        L->pHead = L->pHead->link;
        free(p);
    }
    L->pTail = NULL;
    L->spt = 0;
}

void nhap(Data *x) {
    printf("Nhap ma sv: ");
    scanf("%d", &(x->masv));
    if (x->masv > 0) {
        printf("Nhap ho ten: ");
        scanf("%s", (x->hoten));
        printf("Nhap diem mon 1: ");
        scanf("%f", &(x->d1));
        printf("Nhap diem mon 2: ");
        scanf("%f", &(x->d2));
        printf("Nhap diem mon 3: ");
        scanf("%f", &(x->d3));
    }
}

void in(Data x) {
    printf("Ten: %s, Ma: %d, Diem 1: %.2f, Diem 2: %.2f, Diem 3: %.2f\n",
           x.hoten, x.masv, x.d1, x.d2, x.d3);
}

void processList(LList L) {
    Node *pp = L.pHead;
    while (pp != NULL) {
        in(pp->infor);
        pp = pp->link;
    }
}

int main() {
    LList L;
    int kt = 0;
    int targetID;     
    Node *foundNode;  
    Data x;
    initList(&L);

    do {
        printf("\nChuong trinh lam viec voi DSLK don SV\n");
        printf("\n1: Them nut vao dau danh sach");
        printf("\n2: Them nut vao cuoi danh sach");
        printf("\n3: Them nut vao sau mot nut khac trong danh sach");
        printf("\n4: Xoa sinh vien theo Ma SV");
        printf("\n5: Xoa sinh vien dau danh sach");
        printf("\n6: Xoa sinh vien cuoi danh sach");
        printf("\n7: Tim kiem sinh vien theo Ma SV");
        printf("\n8: Sap xep danh sach tang dan theo Ma SV");
        printf("\n9: Duyet ds");
        printf("\n0: Thoat");
        printf("\nMoi ban chon: ");
        int chon;
        scanf("%d", &chon);

        switch (chon) {
            case 1:
                printf("Nhap thong tin sv can them vao dau:\n");
                nhap(&x);
                if (x.masv > 0) insert_Head(&L, x);
                break;

            case 2:
                printf("Nhap thong tin sv can them vao cuoi:\n");
                nhap(&x);
                if (x.masv > 0) insert_Tail(&L, x);
                break;

            case 3:
                printf("Nhap Ma SV cua nut dung truoc: ");
                scanf("%d", &targetID);
                foundNode = searchByID(L, targetID);
                if (foundNode != NULL) {
                    printf("Nhap thong tin sv moi can chen:\n");
                    nhap(&x);
                    if (x.masv > 0) insert_After(&L, foundNode, x);
                } else {
                    printf("Khong tim thay sinh vien co ma %d!\n", targetID);
                }
                break;

            case 4:
                printf("Nhap Ma SV can xoa: ");
                scanf("%d", &targetID);
                if (delete_ByID(&L, targetID)) {
                    printf("Da xoa sinh vien co ma %d.\n", targetID);
                } else {
                    printf("Khong tim thay sinh vien co ma %d.\n", targetID);
                }
                break;

            case 5:
                delete_Head(&L);
                break;

            case 6:
                delete_Tail(&L);
                break;

            case 7:
                printf("Nhap Ma SV can tim: ");
                scanf("%d", &targetID);
                foundNode = searchByID(L, targetID);
                if (foundNode != NULL) {
                    printf("Thong tin sinh vien:\n");
                    in(foundNode->infor);
                } else {
                    printf("Khong tim thay sinh vien co ma %d.\n", targetID);
                }
                break;

            case 8:
                sort_ByID(&L);
                break;

            case 9:
                processList(L);
                break;

            case 0:
                clearList(&L);
                printf("Da thoat chuong trinh\n");
                kt = 1;
                break;

            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (kt == 0);

    return 0;
}
