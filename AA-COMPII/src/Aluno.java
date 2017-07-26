import java.io.Serializable;



//import java.util.ArrayList;

public class Aluno extends Consumidor  implements Serializable  {

	private String curso;
	
	public String getCurso(){
		return curso;
	}
	public void setCurso(String cursos){
		this.curso = cursos;
	}

	
	public Aluno(String nome, String matricula, String anoIngresso,String cpf, String string){
		
	
			this.setNome(nome);
			this.setMatricula(matricula);
			this.setAnoIngresso(anoIngresso);
			this.curso = string;
			this.setCPF(cpf);
		
		
	}
	public Aluno() {
	}
	
	
}
