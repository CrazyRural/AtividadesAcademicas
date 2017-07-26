import java.net.*;
import java.util.Scanner;
import java.io.*;


public abstract class ClienteJogador {
	
	private static void executar() throws Exception{
		Socket SOCKET = new Socket("localhost", 1050);
		
		while(true){
			Scanner s = new Scanner(System.in);
			String sc = s.nextLine().toUpperCase();
			
			PrintStream PS = new PrintStream(SOCKET.getOutputStream());		
			PS.println(sc);
		
			InputStreamReader IR = new InputStreamReader(SOCKET.getInputStream());
			BufferedReader BR = new BufferedReader(IR);
		
			String mensagemCliente = BR.readLine();
			System.out.println(mensagemCliente);
		}	
		
	}
	public static void main(String[] args) throws Exception {
		executar();
	}
}
