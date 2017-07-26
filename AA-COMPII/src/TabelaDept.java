import java.util.ArrayList;

import javax.swing.JTable;


public class TabelaDept extends JTable{
	
	private static ArrayList<Departamento> rows;
	
	
	public void preenche(){
		for (int i = 0; i < rows.size(); i++) {
			this.setValueAt(rows.get(i).getNome(), i, 0);
			this.setValueAt(rows.get(i).getCodigoDepartamento(), i, 1);
				
		}
	}

	
	public void preencheVazio(){
		for (int i = 0; i < rows.size()+1; i++) {
			this.setValueAt("", i, 0);
			this.setValueAt("", i, 1);
			
		}
	}
	
	@Override
	public boolean isCellEditable(int row,int col){
		return false;
	}

	public TabelaDept(ArrayList<Departamento> rows, String[] columns){
		super(rows.size()+30,columns.length);
		this.rows = rows;
		
		for (int i = 0; i < columns.length; i++) {
			this.getColumnModel().getColumn(i).setHeaderValue(columns[i]);	
		}
		
		this.preenche();
	}
}