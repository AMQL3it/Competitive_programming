/******************************************************************************
 *----------------------------------------------------------------------------*
 *                                                                            *
 *        If the plan does not work, change the plan but not the goal.        *
 *----------------------------------------------------------------------------*
 *        Life is just a life. Lead it, Feel it & Enjoy It Properly.          *
 *        Nothing is impossible. Just believe in yourself & Almighty.         *
 *----------------------------------------------------------------------------*
 *                                                                            *
 *----------------------------------------------------------------------------*
 ******************************************************************************/

#include<bits/stdc++.h>
using namespace std;

///############################# Typedef Section #############################

typedef unsigned int ui;
typedef long long int ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

///############################################################################

///############################# Define Section ###############################
#define FST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define READ          freopen("in.txt","r",stdin)
#define WRITE         freopen("out.txt","w",stdout);
#define nl            "\n"
// #define pi            acos(-1.0)
#define mem(arr,val)  memset(arr,val,sizeof(arr))
#define pb            push_back
#define mp            make_pair
#define pr            pair<ll,ll>
#define ff            first
#define ss            second
#define mod           1000000007
#define INF           1e18
///############################################################################

///############################# Input Section ################################

#define si1(x)        scanf("%d",&x)
#define si2(x,y)      scanf("%d %d", &x, &y)
#define si3(x,y,z)    scanf("%d %d %d", &x, &y, &z)

#define sd1(x)        scanf("%lf",&x)
#define sd2(x,y)      scanf("%lf %lf", &x, &y)
#define sd3(x,y,z)    scanf("%lf %lf %lf", &x, &y, &z)

#define sli1(x)       scanf("%lld",&x)
#define sli2(x,y)     scanf("%lld %lld", &x, &y)
#define sli3(x,y,z)   scanf("%lld %lld %lld", &x, &y, &z)

///############################################################################
///############################### Index Section ##############################
/*
Building Trees:
    1. From pre-order input
    2. From post-order input
    3. From level-order input
    4. From preoder + inorder input
    5. From postorder + inorder input

Traversal Notes:
    1. Pre-order: Root, Left, Right
    2. Post-order: Left, Right, Root
    3. In-order: Left, Root, Right
    4. Level-order: Root, Left, Right (Level by level)

Build Tree Possibility:

✅ শুধুমাত্র Preorder + null markers (-1) → Tree বানানো সম্ভব  
✅ শুধুমাত্র Postorder + null markers (-1) → Tree বানানো সম্ভব  
✅ শুধুমাত্র Level-order + null markers (-1) → Tree বানানো সম্ভব  
✅ শুধুমাত্র Level-order → Tree বানানো সম্ভব → যদি Complete Binary Tree হয়

✅ [Inorder + Preorder] → Tree বানানো সম্ভব → যদি values **unique** হয়  
✅ [Inorder + Postorder] → Tree বানানো সম্ভব → যদি values **unique** হয়  

❌ শুধুমাত্র Inorder (null সহ বা ছাড়া) → Tree বানানো **অসম্ভব**  
❌ শুধুমাত্র Preorder → Tree বানানো **অসম্ভব** (null না থাকলে)  
❌ শুধুমাত্র Postorder → Tree বানানো **অসম্ভব** (null না থাকলে)  
❌ শুধুমাত্র Level-order → Tree বানানো **অসম্ভব**, যদি tree টি Complete না হয়

*/
///############################################################################
///########################## Binary Tree Structure ###########################

struct node {
    int data;
    struct node *left, *right;

    node(int val) {
        data = val;
        left = right = NULL;
    }
};

using Node = node*;

///###################### Tree Construction Functions #########################

// From Preorder with null markers
Node build_tree_from_preorder_with_null(vector<int> &pre_order, int &idx) {
    if (idx >= pre_order.size() || pre_order[idx] == -1) {
        idx++;
        return NULL;
    }

    Node root = new node(pre_order[idx++]);
    root->left = build_tree_from_preorder_with_null(pre_order, idx);
    root->right = build_tree_from_preorder_with_null(pre_order, idx);
    return root;
}

// From Postorder with null markers
Node build_tree_from_postorder_with_null(vector<int> &post_order, int &idx) {
    if (idx < 0 || post_order[idx] == -1) {
        idx--;
        return NULL;
    }

    Node root = new node(post_order[idx--]);
    root->right = build_tree_from_postorder_with_null(post_order, idx);
    root->left = build_tree_from_postorder_with_null(post_order, idx);
    return root;
}

// From Level-order input with null markers
Node build_tree_from_levelorder_with_null(vector<int> &level_order) {
    if (level_order.empty() || level_order[0] == -1) return NULL;

    queue<Node> q;
    Node root = new node(level_order[0]);
    q.push(root);
    int i = 1;

    while (!q.empty() && i < level_order.size()) {
        Node curr = q.front();
        q.pop();

        if (level_order[i] != -1) {
            curr->left = new node(level_order[i]);
            q.push(curr->left);
        }
        i++;

        if (i < level_order.size() && level_order[i] != -1) {
            curr->right = new node(level_order[i]);
            q.push(curr->right);
        }
        i++;
    }

    return root;
}

// From Preorder + Inorder
Node build_tree_from_pre_in(vector<int>& preorder, vector<int>& inorder, int in_start, int in_end, int& pre_idx, unordered_map<int, int>& inorder_map) {
    if (in_start > in_end) return NULL;

    int root_val = preorder[pre_idx++];
    Node root = new node(root_val);

    int in_index = inorder_map[root_val];
    root->left = build_tree_from_pre_in(preorder, inorder, in_start, in_index - 1, pre_idx, inorder_map);
    root->right = build_tree_from_pre_in(preorder, inorder, in_index + 1, in_end, pre_idx, inorder_map);

    return root;
}

// From Postorder + Inorder
Node build_tree_from_post_in(vector<int>& postorder, vector<int>& inorder, int in_start, int in_end, int& post_idx, unordered_map<int, int>& inorder_map) {
    if (in_start > in_end) return NULL;

    int root_val = postorder[post_idx--];
    Node root = new node(root_val);

    int in_index = inorder_map[root_val];
    root->right = build_tree_from_post_in(postorder, inorder, in_index + 1, in_end, post_idx, inorder_map);
    root->left = build_tree_from_post_in(postorder, inorder, in_start, in_index - 1, post_idx, inorder_map);

    return root;
}

///########################## Tree Traversal Functions ########################

// Preorder Traversal
void print_preorder(Node root) {
    if (!root) return;
    cout << root->data << " ";
    print_preorder(root->left);
    print_preorder(root->right);
}

// Inorder Traversal
void print_inorder(Node root) {
    if (!root) return;
    print_inorder(root->left);
    cout << root->data << " ";
    print_inorder(root->right);
}

// Postorder Traversal
void print_postorder(Node root) {
    if (!root) return;
    print_postorder(root->left);
    print_postorder(root->right);
    cout << root->data << " ";
}

// Level-order Traversal
void print_levelorder(Node root) {
    if (!root) return;
    queue<Node> q;
    q.push(root);
    while (!q.empty()) {
        Node curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

///############################# Main Function ###############################

void DenTofieM() {
    // Example Inputs:
    vector<int> pre_order_with_null = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
    vector<int> post_order_with_null = {-1,-1,4,-1,-1,5,2,-1,-1,-1,6,3,1};
    vector<int> level_order_with_null = {1, 2, 3, 4, 5, -1, 6, -1, -1, -1, -1, -1, -1};
    vector<int> preorder = {1, 2, 4, 5, 3, 6};
    vector<int> inorder = {4, 2, 5, 1, 3, 6};
    vector<int> postorder = {4, 5, 2, 6, 3, 1};

    unordered_map<int, int> inorder_map;
    for (int i = 0; i < inorder.size(); i++) {
        inorder_map[inorder[i]] = i;
    }

    // Choose any construction:
    // 1. From Preorder + null
    // int idx = 0;
    // Node root = build_tree_from_preorder_with_null(pre_order_with_null, idx);

    // 2. From Postorder + null
    // int idx = post_order_with_null.size() - 1;
    // Node root = build_tree_from_postorder_with_null(post_order_with_null, idx);

    // 3. From Level-order + null
    // Node root = build_tree_from_levelorder_with_null(level_order_with_null);

    // 4. From Preorder + Inorder
    // int pre_idx = 0;
    // Node root = build_tree_from_pre_in(preorder, inorder, 0, inorder.size() - 1, pre_idx, inorder_map);

    // 5. From Postorder + Inorder
    int post_idx = postorder.size() - 1;
    Node root = build_tree_from_post_in(postorder, inorder, 0, inorder.size() - 1, post_idx, inorder_map);

    // Output Traversals
    cout << "Preorder: "; print_preorder(root); cout << nl;
    cout << "Inorder: "; print_inorder(root); cout << nl;
    cout << "Postorder: "; print_postorder(root); cout << nl;
    cout << "Levelorder: "; print_levelorder(root); cout << nl;
}

int main() {
    FST_IO
    DenTofieM();
    return 0;
}