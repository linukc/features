## Basic commands
* <http://rightblog.ru/3274>
* <https://github.com/splincode/habrahabr-articles/tree/master/git>
* <http://johnatten.com/2012/09/08/basic-git-command-line-reference-for-windows-users/>
## Manual
* [extensive guide](https://git-scm.com/book/ru/v1/Îñíîâû-Git-Ñîçäàíèå-Git-ðåïîçèòîðèÿ)
* [basic instructions](https://proglib.io/p/git-for-half-an-hour/)
* [nicely done](https://www.atlassian.com/git/tutorials/learn-git-with-bitbucket-cloud)
* [great servies](https://githowto.com/ru/)
## Useful commands
### Preparation  
git config --global user.name "Your Name"  
git config --global user.email "your_email@whatever.com"  
### Creating a Project  
git init  
git add (git add .)    
git commit -m "Commit message"  
### Checking the status of the repository  
git status  
### History  
git log  
git history (git config --global alias.history "log --pretty=format:'%h %ad | %s%d [%an]' --graph --date=short")  
### Getting older versions  
git checkout \<hash\>  
git checkout master (return to latest version) 
### Print file
git cat \<file\>
### Tagging versions  
git tag    
git checkout \<tag\>^ (return to version before \<tag\>)    
git checkout \<tag\>  
git tag \<name\>  
git history master --all  
### Cancel local changes (before staging)  
Change file  
git checkout \<file\>  
### Cancel Staged changes (before committing)  
Change file  
git add \<file\>  
git reset HEAD \<file\>  
git checkout \<file\>  
### Cancelling commits  
Change file 
git add \<file\>  
git commit -m "Message commit"  
git revert HEAD (add the commmit which cancel HEAD commit) or  
git revert \<hash\> (if want leave editor press "esc" + input ":wq")  
### Removing a commit from a branch  
git reset --hard \<tag\> 
git history --all  
(if we give tag to the last commit after this operation we can whatever see   
the "delete" commit because he is still in repository)
### Change push url
git remote -v  
View existing remotes  
origin  https://github.com/user/repo.git (fetch)  
origin  https://github.com/user/repo.git (push)  

git remote set-url origin https://github.com/user/repo2.git  
Change the 'origin' remote URL    
git remote -v  
Verify new remote URL  
origin  https://github.com/user/repo2.git (fetch)  
origin  https://github.com/user/repo2.git (push)  



