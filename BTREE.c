#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
};

typedef struct node BTREE;

BTREE *New_Mode(int x) {
   BTREE *root = (BTREE *)malloc(sizeof(BTREE));
   root->data = x;
   root->height = 0;
   root->left = NULL;
   root->right = NULL;
   return root;
}

BTREE *Insert(BTREE *root,int x) {
    if (root != NULL)
    {
        if (x> root->data)
        {
           root->right= Insert(root->right,x);     
        }
        else if (x<root->data)
        {
            root->left= Insert(root->left,x);
        } 
    }
    else
    {
       root->data = x; 
        root = New_Mode(root->data);
    }
    
    return root;
}

BTREE *Delete(BTREE *root,int x){
    if (root == NULL ) {
         return NULL;
    }
    BTREE *p,*q;

    if (root->data==x)
    {
        if (root->left== root->right)
        {
           free(root);
           return NULL;
        }
        else if (root->left== NULL)
        {
            p= root->right;
            free(root);
            return p;
        }  
        else if (root->right== NULL)
        {
            p=root->left;
            free(root);
            return p;
        }
        
        else
        {
            p = q = root -> right;
            while(p -> left != NULL)
            p = p -> left;
            p -> left = root -> left;
            free(root);
            return q;

        }
        
    }
    else if(root -> data < x)
        root -> right = delete_node(root -> right, x);
    else
        root -> left = delete_node(root -> left, x);
    return root;
}

int height(BTREE *root) {
    if(root == NULL) {
        return -1;
    }   
    else
    {
        int height_left,height_right;
        height_left  = height(root -> left);
        height_right= height(root->right);

        if( height_right > height_left ) 
            return height_right + 1;
        else
            return height_left + 1;
    }
    
}
BTREE *Left_Rotate(BTREE *root) {
    BTREE * temp = root->right;
    root->left = temp->right;
    temp->right = root;
    return temp;
}

BTREE *Right_Rotate(BTREE *root) {
    BTREE *temp = root->left;
    root->right = temp->left;
    temp->left = root;

    return temp;
}

BTREE *LeftToRight(BTREE *root) {
   root->left = Left_Rotate(root->left);

   return Right_Rotate(root);
}

BTREE *RightToLeft(BTREE *root) {
  root->right = Right_Rotate(root->right);

  return Left_Rotate(root);  
}

int GetBalance(BTREE *root) {
  if (root == NULL)
  {
    return 0;
  }
  return height(root->left)- height(root->right);
}


BTREE *Delete_AVL(BTREE *root, int x){
    if (root == NULL)
    {
       return NULL;
    }
    if (x<root->data)
    {
        x = root->data;
      root->left = Delete_AVL(root->left,x);
    }
    else if (x>root->data)
    {
        x = root->data;   
        root->right = Delete(root->right,x);
    }
    else
    {
            if((root -> left == NULL) || (root -> right == NULL)) {
            BTREE *temp = root -> left ? root -> left : root -> right;
        /* Eğer çocuk yoksa temp NULL değerini alıyor fakat bir çocuk varsa,
        çocuk temp'e atanıyor */
        if(temp == NULL) { // eğer silinecek düğümün hiç çocuğu yoksa
        temp = root;
        root = NULL;
        } else // eğer silinecek düğümün bir çocuğu varsa
        *root = *temp; // çocuk ebeveyninin yerine geçiyor
        free(temp); // temp siliniyor
        } else { // eğer silinecek düğümün iki çocuğu varsa
        BTREE *temp = minValue(root -> right);
        // sağ alt ağacında en küçük veriye sahip olan düğüm bulunuyor
        root -> data = temp -> data;
        // bulunan minimum değer silinecek düğüme kopyalanıyor
        root -> right = deleteNode(root -> right, temp -> data);
        /* Artık silinecek değer temp'tedir. Fonksiyon kendisini sağ çocuğu ve
        Silinecek temp değeriyle tekrar çağırıyor */
        }
        }
        if (root == NULL)
        return root;
        // Ağacın yüksekliği güncelleniyor
        root -> height = max(height(root -> left), height(root -> right)) + 1;
        // Eğer balans 1’den büyükse ve sol alt ağacın balansı 0’dan büyük veya eşitse
        if (getBalance(root) > 1 && getBalance(root -> left) >= 0)
        return rightRotate(root); // sağa döndür
        // Eğer balans 1’den büyükse ve sol alt ağacın balansı 0’dan küçükse
        if (getBalance(root) > 1 && getBalance(root -> left) < 0) {
        root -> left = leftRotate(root -> left); // ilk önce sola döndür
        return rightRotate(root); // sonra sağa döndür
        }
        // Eğer balans -1’den küçükse ve sağ alt ağacın balansı 0’dan küçük veya eşitse
        if (getBalance(root) < -1 && getBalance(root -> right) <= 0)
        return leftRotate(root); // sola döndür
        // Eğer balans -1’den küçükse ve sağ alt ağacın balansı 0’dan büyükse
        if (getBalance(root) < -1 && getBalance(root -> right) > 0) {
        root -> right = rightRotate(root -> right); // ilk olarak sağa döndür
        return leftRotate(root); // sonra sola döndür
        }
        return root; 
}

void MaxHeap ( int *array, int x, int index) {
    if (index == 100)
    {
     printf("Heap is full"); 
    }
    else
    {
      array [index] =x;
      while (index !=1 && array[index/2] <array [index])
      {
       swap(&array[index/2], &array[index]); 
       index/=2;
      }
        
    }
    
} 
int main()
{
    
    return 0;
}
