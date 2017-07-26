import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;


public class DataBase implements Serializable {


	private ArrayList<Aluno> alunos = new ArrayList<Aluno>();
	
	private ArrayList<Funcionario> funcionario = new ArrayList<Funcionario>();
	
	private ArrayList<Curso> curso = new ArrayList<Curso>();
	
	private ArrayList<Departamento> dept = new ArrayList<Departamento>();
	
	public ArrayList<Aluno> getAlunos() {
		return alunos;
	}

	public void setAlunos(ArrayList<Aluno> alunos) {
		this.alunos = alunos;
	}
	
	public ArrayList<Funcionario> getFuncionario() {
		return funcionario;
	}

	public void setFuncionario(ArrayList<Funcionario> funcionario) {
		this.funcionario = funcionario;
	}

	
	public ArrayList<Curso> getCurso() {
		return curso;
	}

	public void setCurso(ArrayList<Curso> curso) {
		this.curso = curso;
	}
	
	public ArrayList<Departamento> getDept() {
		return dept;
	}

	public void setDept(ArrayList<Departamento> dept) {
		this.dept = dept;
	}	
	
	public DataBase(){
		
	}

	
}
