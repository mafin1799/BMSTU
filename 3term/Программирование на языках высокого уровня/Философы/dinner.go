package main

import (
	"fmt"
	"log"
	"net/http"
	"sync"
	"time"

	"golang.org/x/net/websocket"
)

const (
	num = 5
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		http.ServeFile(w, r, "index.html")
	})
	http.Handle("/think", websocket.Handler(think))

	log.Print("Server runing on localhost:8080")
	log.Fatal(http.ListenAndServe(":8080", nil))
}

func think(ws *websocket.Conn) {
	var (
		output = make(chan string)
		forks  = make([]sync.Mutex, num)
	)
	var thinkingTime, foodTime [num]int
	for i := 0; i < num; i++ {
		thinkingTime[i] = genTimeThink(i)
		foodTime[i] = genTimeFoof(i)
	}
	for i := 1; i < num; i++ {
		go philosopher(i, thinkingTime[i], foodTime[i], forks, i, i-1, output)
	}
	// Нулевой философ - левша.
	go philosopher(0, thinkingTime[0], foodTime[0], forks, num-1, 0, output)

	for {
		websocket.Message.Send(ws, <-output)
	}
}

func philosopher(id, thinkingTime, foodTime int, forks []sync.Mutex, leftFork, rightFork int, output chan string) {
	for {

		output <- format("phil", id, "think")
		time.Sleep(time.Duration(thinkingTime) * time.Millisecond)
		output <- format("phil", id, "wait")

		var (
			leftForkAction  = "right"
			rightForkAction = "left"
		)
		if id == 0 {
			leftForkAction = "left"
			rightForkAction = "right"
		}

		forks[leftFork].Lock()
		output <- format("fork", leftFork, leftForkAction)
		forks[rightFork].Lock()
		output <- format("fork", rightFork, rightForkAction)

		output <- format("phil", id, "eat")
		time.Sleep(time.Duration(foodTime) * time.Millisecond)
		output <- format("phil", id, "wait")

		forks[rightFork].Unlock()
		output <- format("fork", rightFork, "back")
		forks[leftFork].Unlock()
		output <- format("fork", leftFork, "back")

	}
}

func format(who string, id int, action string) string {
	return fmt.Sprintf(`{"who": "%s", "id": %d, "action": "%s"}`, who, id, action)
}
func genTimeFoof(id int) int {
	var time1 int
	fmt.Println("Введите время еды для философа", id+1)
	fmt.Scan(&time1)
	return time1 * 1000
}

func genTimeThink(id int) int {
	var time1 int
	fmt.Println("Введите время размышлений для философа", id+1)
	fmt.Scan(&time1)
	return time1 * 1000
}
