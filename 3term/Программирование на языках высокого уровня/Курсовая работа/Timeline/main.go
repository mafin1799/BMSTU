package main

import (
	"database/sql"
	"fmt"
	_ "github.com/go-sql-driver/mysql"
	"github.com/gorilla/mux"
	"html/template"
	"net/http"
	"sort"
)

type Article struct {
	Id      int16
	Pid     int16
	Path    string
	Heading string
	Text    string
	Date    string
}

type form2level struct {
	Id      int16
	Heading string
}

var posts []Article
var data2level []form2level

func showPost(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	t, err := template.ParseFiles("header.html", "index.html", "glush.html")
	if err != nil {
		fmt.Fprintf(w, err.Error())
	}
	connection().Close()
	res, err := connection().Query(fmt.Sprintf("SELECT * FROM `articles` WHERE `pid` = '%s'", vars["id"]))
	if err != nil {
		panic(err)
	}
	posts = selection(res, 1)
	if len(posts) < 4 {
		t.ExecuteTemplate(w, "glush", nil)
	} else {
		t.ExecuteTemplate(w, "index", posts)
	}
}

func index(w http.ResponseWriter, r *http.Request) {
	t, err := template.ParseFiles("header.html", "index.html")
	if err != nil {
		fmt.Fprintf(w, err.Error())
	}
	connection().Close()
	res, err := connection().Query("SELECT * FROM `articles`")
	if err != nil {
		panic(err)
	}
	posts = selection(res, 0)
	err1 := t.ExecuteTemplate(w, "index", posts)
	if err1 != nil {
		return
	}
}

func save_article(w http.ResponseWriter, r *http.Request) {
	Heading := r.FormValue("heading")
	Text := r.FormValue("text")
	Path := r.FormValue("path")
	Date := r.FormValue("date")
	connection().Close()
	insert, err := connection().Query(fmt.Sprintf("INSERT INTO `articles` (`Heading`, `Text`,`Path`,`Date`) VALUES('%s', '%s','%s', '%s')", Heading, Text, Path, Date))
	if err != nil {
		panic(err)
	}
	defer insert.Close()
	http.Redirect(w, r, "/", http.StatusSeeOther)
}

func saveArticle2level(w http.ResponseWriter, r *http.Request) {
	Pid := r.FormValue("pid")
	Heading := r.FormValue("heading")
	Text := r.FormValue("text")
	Path := r.FormValue("path")
	Date := r.FormValue("date")
	connection().Close()
	insert, err := connection().Query(fmt.Sprintf("INSERT INTO `articles` (`Pid`,`Heading`, `Text`,`Path`,`Date`) VALUES('%s','%s', '%s','%s', '%s')", Pid, Heading, Text, Path, Date))
	if err != nil {
		panic(err)
	}
	defer insert.Close()
	http.Redirect(w, r, "/", http.StatusSeeOther)

}
func create(w http.ResponseWriter, r *http.Request) {
	t, err := template.ParseFiles("header.html", "create.html")
	if err != nil {
		fmt.Fprintf(w, err.Error())
	}
	t.ExecuteTemplate(w, "view", nil)
}

func create2(w http.ResponseWriter, r *http.Request) {
	t, err := template.ParseFiles("header.html", "create2.html")
	if err != nil {
		fmt.Fprintf(w, err.Error())
	}
	connection().Close()
	res, err := connection().Query("SELECT id, heading FROM `articles`")
	if err != nil {
		panic(err)
	}
	data2level = data2level[:0]
	for res.Next() {
		var data form2level
		err = res.Scan(&data.Id, &data.Heading)
		if err != nil {
			panic(err)
		}
		data2level = append(data2level, data)
	}
	sort.Slice(data2level, func(i, j int) (less bool) {
		return data2level[i].Id < data2level[j].Id
	})
	t.ExecuteTemplate(w, "view2", data2level)
}
func main() {
	HandleRequests()
}

func HandleRequests() {
	rtr := mux.NewRouter()
	rtr.HandleFunc("/", index).Methods("GET")
	rtr.HandleFunc("/about/", create).Methods("GET")
	rtr.HandleFunc("/about2/", create2).Methods("GET")
	rtr.HandleFunc("/save_article", save_article).Methods("POST")
	rtr.HandleFunc("/saveArticle2level", saveArticle2level).Methods("POST")

	rtr.HandleFunc("/post/{id:[0-9]+}", showPost).Methods("GET")
	http.Handle("/", rtr)
	http.Handle("/static/", http.StripPrefix("/static", http.FileServer(http.Dir("./static/"))))
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		return
	}
}

func connection() *sql.DB {
	db, err := sql.Open("mysql", "root:root@tcp(127.0.0.1:3306)/goland")
	if err != nil {
		panic(err)
	}
	return db
}

func selection(res *sql.Rows, flag int) []Article {
	posts = posts[:0]
	for res.Next() {
		var post Article
		err := res.Scan(&post.Id, &post.Pid, &post.Heading, &post.Text, &post.Path, &post.Date)
		if err != nil {
			panic(err)
		}
		if flag == 0 && post.Pid == 0 {
			posts = append(posts, post)
		} else if flag == 1 {
			posts = append(posts, post)
		}
	}
	sort.Slice(posts, func(i, j int) (less bool) {
		return posts[i].Date < posts[j].Date
	})
	return posts
}
