import java.io.Serializable;
import java.util.InputMismatchException;


public abstract class Consumidor  implements Serializable {	

	private String nome;
	private String matricula;//nao existem 2 matriculas iguais
	private String anoIngresso;
	private String CPF;//nao existem 2 CPF iguais
	private Sexo sexo;
	private Titulo titulo;
	private float ticketsComprados = 0;
	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public String getMatricula() {
		return matricula;
	}
	public void setMatricula(String matricula) {
		this.matricula = matricula;
	}
	public String getAnoIngresso() {
		return anoIngresso;
	}
	public void setAnoIngresso(String anoIngresso) {
		this.anoIngresso = anoIngresso;
	}
	public String getCPF() {
		return CPF;
	}
	public void setCPF(String cPF) {
		CPF = cPF;
	}
	public Titulo getTitulo() {
		return titulo;
	}
	public void setTitulo(Titulo titulo) {
		this.titulo = titulo;
	}
	public Sexo getSexo() {
		return sexo;
	}
	public void setSexo(Sexo sexo) {
		this.sexo = sexo;
	}
	public float getTicketsComprados() {
		return ticketsComprados;
	}
	public void setTicketsComprados(float ticketsComprados) {
		this.ticketsComprados = ticketsComprados;
	}
	//-------------------------------------------------//
		//metodos do consumidor//
	public static boolean validadeCPF(String CPF) { 
		
		
		   if(CPF.equals("00000000000") || CPF.equals("11111111111") 
		     ||CPF.equals("22222222222") || CPF.equals("33333333333") 
			 || CPF.equals("44444444444") || CPF.equals("55555555555") 
			 || CPF.equals("66666666666") || CPF.equals("77777777777") 
			 || CPF.equals("88888888888") || CPF.equals("99999999999") 
			 || (CPF.length() != 11)) return(false); 
			
			char dig10, dig11; 
			int total, i, r, num, n; 
				
			try { 
				total = 0; 
				n = 10; 
				for (i=0; i<9; i++) { 
					
					num = (int)(CPF.charAt(i) - 48);	
					total = total + (num * n); 
					n --;		
				}
				
				r = 11 - (total % 11);
				
				if ((r == 10) || (r == 11))					
					dig10 = '0';
				else
					dig10 = (char)(r + 48); 
				    total = 0;
					n = 11;
					
				for(i=0; i<10; i++) 
				{ 
						num = (int)(CPF.charAt(i) - 48);
						total = total + (num * n); 
						n--;
						
				} 
						r = 11 - (total % 11);
						
				if ((r == 10) || (r == 11)) 
					dig11 = '0';
				else dig11 = (char)(r + 48); 
				
				 
				if ((dig10 == CPF.charAt(9)) && (dig11 == CPF.charAt(10)))
					return(true);  
				else 
					return(false);
				} catch (InputMismatchException erro)
				{
					return(false); 
						
				} 		
	}

}
