external gui : unit -> int = "gui"
external maj : string -> unit = "maj"

let parse coord =
  let read_channel = open_in coord in
  let read = ref (input_line read_channel) in
  let len = ref 0 in
  let com = ref false in
  let instr = ref "" in
  let char = ref 'a' in
    while not(!read = "\n") do
      read := input_line read_channel
    done;
    try
      while true do
	read := input_line read_channel;
	len := String.length(!read);
	for i = 0 to !len do
	  char := String.get !read i;
	  if not !com then
	    match !char with
	      |'%'|'{'->com := true
	      |' '|'\n'-> maj !instr;instr := ""
	      |c->instr := !instr ^Char.escaped(c)
	  else
	    if !char = '}' then
	      com := false
	done;
      done;
!instr
    with
	End_of_file ->close_in read_channel;!instr


      
(*MàJ des int(bb) via une surcouche en temps réel et de l'echiquier via change_position + store des string dans une liste*)

let _ = Callback.register "parser" parse

let main () =
  let a = gui () in 
  exit a

let _ = main()
