#include "git_simulation.h"
using namespace std;

commitment::commitment(string msg) {

    message=msg;

}
string commitment::getmessage_commit() const {

    return message;

}



File::File(string n) {


    name = n;

}
string File::getName() const {

    return name;

}


Repository::Repository(string n, bool pub) {

    name=n;

    this->pub=pub;

    commitCount=0;
}

void Repository::addCommit(const commitment& commit, const string& message) {
    commits.push_back(commit);
    commitMessages.push_back(message); 
}

vector<string> Repository::Messages_commits() const {
    vector<string> messages;
    for (size_t i = 0; i < commits.size(); i++) {
        messages.push_back(commits[i].getmessage_commit());
    }
    return messages;
}


void Repository::set_Commit_Count(int count) {
    commitCount = count;
}

const vector<commitment>& Repository::getCommits() const {
    return commits;
}

string Repository::getName() const {
    return name;
}

bool Repository::Public_repository() const {
    return pub;
}

void Repository::addFile(const File& file) {
    files.push_back(file);
}

void Repository::deleteFile(const string& fileName) {
    for (vector<File>::iterator it = files.begin(); it != files.end(); ++it) {
        if (it->getName() == fileName) {
            files.erase(it);
            break;
        }
    }
}


const vector<File>& Repository::getFiles() const {
    return files;
}

void Repository::addCommit(const commitment& commit) {
    commits.push_back(commit);
}

int Repository::getFileCount() const {
    return files.size();
}

int Repository::Commit_Count() const {
    return commits.size();
}


treeimplmentation::treeimplmentation(Repository* r) : repo(r) {}
treeimplmentation::~treeimplmentation() {
    delete repo;
    for (unordered_map<string, treeimplmentation*>::iterator it = children.begin(); it != children.end(); ++it) {
        delete it->second;
    }
}
treeimplmentation* treeimplmentation::addChild(const std::string& name, Repository* repo) {
    treeimplmentation* newNode = new treeimplmentation(repo);
    children[name] = newNode;
    return newNode;
}

Repository* treeimplmentation::get_Repository() const {
    return repo;
}

std::unordered_map<std::string, treeimplmentation*>& treeimplmentation::getChildren() {
    return children;
}


User::User() {

    username = "";;
    password="";
    followers=0;


}
User::User(string n, string p) {

    username = n;
     password=p;
    followers=0;

}

string User::get_Username() const {
    return username;
}

string User::get_Password() const {
    return password;
}

int User::getFollowers() const {
    return followers;
}

void User::Followers_add() {
    followers++;
}

void User::Followers_delete() {
    followers--;
}

githupsimulation::githupsimulation() {}

void githupsimulation::addfile(const string& username, const string& repoName, const string& fileName) {

    if (userRepositories.find(username) == userRepositories.end()) {
        cout << "The User not exist" << endl;
        return;
    }

    treeimplmentation* root = userRepositories[username];

    if (root->getChildren().find(repoName) == root->getChildren().end()) {
        cout << "THE Repository  is not exist" << endl;
        return;
    }

    
    Repository* repo = root->getChildren()[repoName]->get_Repository();

    
    File newFile(fileName);
    repo->addFile(newFile);

   
    cout << "The File is  added to repository " << endl;
     writerepo();
}

void githupsimulation::deletefile(const string& username, const string& repoName, const string& fileName) {
    
    if (userRepositories.find(username) == userRepositories.end()) {
        cout << "The User is  not exist" << endl;
        return;
    }

    treeimplmentation* root = userRepositories[username];

    if (root->getChildren().find(repoName) == root->getChildren().end()) {
        cout << "The Repository  is not exist" << endl;
        return;
    }

   
    Repository* repo = root->getChildren()[repoName]->get_Repository();

    
    repo->deleteFile(fileName);

    
    cout << "The File deleted from repository " << endl;
     writerepo(); 
}

void githupsimulation::userdataread() {
    ifstream userFile("login.csv");
    string line;

    while (getline(userFile, line)) {
        stringstream ss(line);
        string username, password;

        getline(ss, username, ',');
        getline(ss, password, ',');

        users[username] = User(username, password);
    }

    userFile.close();
}


void githupsimulation::userwritedata() {
    ofstream userFile("login.csv");

    for (auto const& pair : users) {
        userFile << pair.second.get_Username() << "," << pair.second.get_Password() << "," << pair.second.getFollowers() << endl; // Include followers count
    }

    userFile.close();
}

void githupsimulation::readrepo() {
    ifstream repoFile("data.csv");
    string line;

    while (getline(repoFile, line)) {
        stringstream ss(line);
        string user_n, r, ps, commitCountStr, cf, total_files;

        getline(ss, user_n, ',');
        getline(ss, r, ',');
        getline(ss, ps, ',');
        getline(ss, commitCountStr, ',');
        getline(ss, cf, ',');
        getline(ss, total_files, ',');

     
        bool isPublic;
        int total_com, total_f;

        try {
            isPublic = stoi(ps);
            total_com = stoi(commitCountStr);
            total_f = stoi(cf);
        }
        catch (const invalid_argument& e) {
          
            cerr << "exception is in  format of CSV: " << e.what() << endl;
            continue;
        }
        catch (const out_of_range& e) {
           
            cerr << "the out of range error in conversion: " << e.what() << endl;
            continue;
        }

        Repository* repo = new Repository(r, isPublic);

        for (int i = 0; i < total_f; ++i) {
            string fileName;
            getline(ss, fileName, ',');
            repo->addFile(File(fileName));
        }

       
        if (userRepositories.find(user_n) == userRepositories.end()) {
            treeimplmentation* root = new treeimplmentation(nullptr);
            userRepositories[user_n] = root;
        }

      
        treeimplmentation* root = userRepositories[user_n];

       
        root->addChild(r, repo);
    }

    repoFile.close();
}


void githupsimulation::writerepo() {
    ofstream repoFile("data.csv");

    for (auto const& userPair : userRepositories) {
        for (auto const& repoPair : userPair.second->getChildren()) {
            Repository* repo = repoPair.second->get_Repository();
            string username = userPair.first;
            string repoName = repo->getName();
            bool visibility = repo->Public_repository();
            int commitCount = repo->Commit_Count();
            int fileCount = repo->getFileCount();
            const vector<File>& files = repo->getFiles();
            const vector<commitment>& commits = repo->getCommits(); 

            repoFile << username << "," << repoName << "," << visibility << "," << commitCount << "," << fileCount;

           
            for (const auto& commit : commits) {
                repoFile << "," << commit.getmessage_commit();
            }

         
            for (const auto& file : files) {
                repoFile << "," << file.getName();
            }

            repoFile << endl;
        }
    }

    repoFile.close();
}

int githupsimulation::countfork(const string& username, const string& repoName) {
    int count = 0;
    for (auto const& userPair : userRepositories) {
        if (userPair.first != username) {
            treeimplmentation* root = userPair.second;
            if (root->getChildren().find(repoName) != root->getChildren().end()) {
                count++;
            }
        }
    }
    return count;
}

void githupsimulation::registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    if (users.find(username) != users.end()) {
        cout << "The username already  exist" << endl;
        return;
    }

    cout << "Enter the  password: ";
    cin >> password;

    users[username] = User(username, password);
    userwritedata();
    cout << "Registration successful!" << endl;
}


void githupsimulation::login(string& loggedInUser) {
    string username, password;
    cout << "Enter the  username: ";
    cin >> username;

    if (users.find(username) == users.end()) {
        cout << "The User not found" << endl;
        return;
    }

    cout << "enter the password: ";
    cin >> password;

    if (users[username].get_Password() == password) {
        cout << "Login successful" << endl;
        loggedInUser = username;
    }
    else {
        cout << "Incorrect password" << endl;
    }
}

void githupsimulation::logout(string& loggedInUser) {
    cout << "Logout successful" << endl;
    loggedInUser = "";
}
void githupsimulation::viewProfile(const string& usernameToView) {
    if (users.find(usernameToView) == users.end()) {
        cout << "User not found!" << endl;
        return;
    }

    cout << "the user: " << users[usernameToView].get_Username() << endl;
    cout << "Followers: " << users[usernameToView].getFollowers() << endl;
}

void githupsimulation::createRepository(const string& username, const string& repoName, bool isPublic, int commitCount) {
    
    if (userRepositories.find(username) == userRepositories.end()) {
        treeimplmentation* root = new treeimplmentation(nullptr);
        userRepositories[username] = root;
    }

    
    treeimplmentation* root = userRepositories[username];

    
    if (root->getChildren().find(repoName) == root->getChildren().end()) {
        Repository* repo = new Repository(repoName, isPublic);

      
        for (int i = 0; i < commitCount; ++i) {
            commitment commit(" commit");
            repo->addCommit(commit);
        }

        root->addChild(repoName, repo);
    }
    else {
        cout << "the repository  already exists " << endl;
        return;
    }

   
    cout << "Repository created successfully!" << endl;
}

void githupsimulation::deleteRepository(const string& username, const string& repoName) {
   
    if (userRepositories.find(username) == userRepositories.end()) {
        cout << " not found!" << endl;
        return;
    }

    
    treeimplmentation* root = userRepositories[username];

  
    if (root->getChildren().find(repoName) == root->getChildren().end()) {
        cout << "Repository not found!" << endl;
        return;
    }

    
    delete root->getChildren()[repoName];
    root->getChildren().erase(repoName);

   
    cout << "Repository deleted successfully" << endl;
    writerepo();
}

void githupsimulation::Fork(const string& sourceUsername, const string& sourceRepoName, const string& targetUsername) {
   
    if (userRepositories.find(sourceUsername) == userRepositories.end()) {
        cout << "the source  not found" << endl;
        return;
    }

    treeimplmentation* sourceRoot = userRepositories[sourceUsername];

    if (sourceRoot->getChildren().find(sourceRepoName) == sourceRoot->getChildren().end()) {
        cout << "the source not found" << endl;
        return;
    }

  
    Repository* sourceRepo = sourceRoot->getChildren()[sourceRepoName]->get_Repository();

    
    cout << "the commit messages of  fork:" << endl;
    const vector<commitment>& sourceCommits = sourceRepo->getCommits();
    for (const auto& commit : sourceCommits) {
        cout << "- " << commit.getmessage_commit() << endl;
    }

    
    createRepository(targetUsername, sourceRepoName, sourceRepo->Public_repository(), sourceRepo->Commit_Count()); // Pass commit count

   
    treeimplmentation* targetRoot = userRepositories[targetUsername];
    Repository* targetRepo = targetRoot->getChildren()[sourceRepoName]->get_Repository();

    
    const vector<File>& sourceFiles = sourceRepo->getFiles();
    for (const auto& file : sourceFiles) {
        targetRepo->addFile(file); 
    }

    
    for (const auto& commit : sourceCommits) {
        targetRepo->addCommit(commit); 
    }

   
    cout << "the repository forked successfully add" << endl;
    writerepo();

 
}

void githupsimulation::commitToRepository(const string& username, const string& repoName, const string& message) {
   
    if (userRepositories.find(username) == userRepositories.end()) {
        cout << "the user not found" << endl;
        return;
    }

    treeimplmentation* root = userRepositories[username];

    if (root->getChildren().find(repoName) == root->getChildren().end()) {
        cout << "the repository not found" << endl;
        return;
    }

    
    Repository* repo = root->getChildren()[repoName]->get_Repository();

   
    commitment commit(message);

    
    repo->addCommit(commit, message);

   
    cout << "the commit added now " << endl;
    writerepo();
}

void githupsimulation::Statsrepository(const string& username, const string& repoName) {
   
    if (userRepositories.find(username) == userRepositories.end()) {
        cout << "the user is  not found" << endl;
        return;
    }

    treeimplmentation* root = userRepositories[username];

    if (root->getChildren().find(repoName) == root->getChildren().end()) {
        cout << "the repository  is not found" << endl;
        return;
    }

    
    Repository* repo = root->getChildren()[repoName]->get_Repository();

  
    int forkCount = countfork(username, repoName);

  
    cout << "the repository name : " << repo->getName() << endl;
    cout << "the file number : " << repo->getFileCount() << endl;
    cout << "the commintment message : " << repo->Commit_Count() << endl;
    cout << "the total no of fork: " << forkCount << endl;

   
    cout << "the commit messages is :" << endl;
    const vector<string>& commitMessages = repo->Messages_commits();
    for (size_t i = 0; i < commitMessages.size(); ++i) {
        cout << i + 1 << ". " << commitMessages[i] << endl;
    }
}


void githupsimulation::  Folllow(const string& follower, const string& following) {
    if (users.find(follower) == users.end() || users.find(following) == users.end()) {
        cout << "no user found !" << endl;
        return;
    }

    followGraph[follower].insert(following);
    users[follower].Followers_add();
    cout << follower << " is now follow  " << following << endl;
}

void githupsimulation::Unfolllow(const string& follower, const string& following) {
   
    bool Find_Follow = users.find(follower) != users.end();
    bool followingFound = users.find(following) != users.end();

    if (!Find_Follow || !followingFound) {
        cout << "no user exist " << endl;
        return;
    }

   
    bool isFollowing = false;
    auto add_f = followGraph.find(follower);
    if (add_f != followGraph.end()) {
        auto followingIt = add_f->second.find(following);
        if (followingIt != add_f->second.end()) {
            add_f->second.erase(followingIt);
            isFollowing = true;
        }
    }

    if (isFollowing) {
        users[follower].Followers_delete();
        cout << follower << " is unfollow " << following << endl;
    }
    else {
        cout << follower << " was not follow " << following << endl;
    }
}
