

// the worker script to enable threading in the program
WorkerScript.onMessage = function(message) {
    WorkerScript.sendMessage({'role': message.role, 'content':message.content})
    console.log("[DEBUG] New message send")
}
