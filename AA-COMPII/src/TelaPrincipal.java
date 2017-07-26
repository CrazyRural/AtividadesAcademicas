import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.DefaultComboBoxModel;


public class TelaPrincipal {


	public static JFrame frame;
	private JTextField textField;
	//private JTable tabela;
	//tabelas
	
	public static TabelaAlunos tabela;
	public static TabelaFunc tabela1;
	public static TabelaCursos tabela2;
	public static TabelaDept tabela3;
	//scroll panes
	public static JScrollPane rolagem;
	public static JScrollPane rolagem1;
	public static JScrollPane rolagem2;
	public static JScrollPane rolagem3;
	public static JScrollPane desjejumScroll;
	public static JScrollPane almocoScroll;
	public static JScrollPane jantarScroll;
	
	public static DataBase db = new DataBase();
	
	public static Almoco almoco = new Almoco();
	public static Desjejum desjejum = new Desjejum();
	public static Jantar jantar = new Jantar();

	public static JLayeredPane abarefeicao;
	public static JLayeredPane abatickets; 
	public static JLayeredPane Desjejum; 
	public static JLayeredPane Almoco;
	public static JLayeredPane Jantar;

	public static JList desjejumLista;
	public static JList almocoLista;
	public static JList jantarLista;
	
	public static JComboBox comboBox1;
	public static JComboBox comboBox;

	public static String [] colunasAlunos = {"Nome do Aluno", "Matricula", "Ano de Ingresso","Curso","Tickets Comprados"};
	String [] colunasFuncionarios = {"Nome do Funcionario", "CPF", "Ano de Ingresso","Departamento","Tickets Comprados"};
	String [] colunasCurso = {"Nome do Curso","Sigla do Curso","Departamento"};
	String [] colunasDept = {"Nome do Departamento","Sigla do Departamento"};
	String [] listaAlunos;	
	String [] listaFuncionarios;

	public JTable getTabela(){
		return TelaPrincipal.tabela;
	}
	public JTable getTabela1(){
		return TelaPrincipal.tabela1;
	}
	public JTable getTabela2(){
		return TelaPrincipal.tabela2;
	}
	public JTable getTabela3(){
		return TelaPrincipal.tabela3;
	}
	public TelaPrincipal() {
		
	//	db = SerializaDataBase.DesserializarDataBase("FileName");
	//	System.out.println(db.getCurso().get(0).getNome());
		
		frame = new JFrame();
		frame.setBounds(300, 100, 800, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("Controle do R.U. (v1.0b)");
		ImageIcon img = new ImageIcon("C:\\Users\\Joao Victor Araujo\\Desktop\\Icons\\restaurant26.png");
		frame.setIconImage(img.getImage());

		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		frame.getContentPane().add(tabbedPane, BorderLayout.CENTER);

		//Aba Alunos-------------------------------------------------------------------------------------
		JLayeredPane abaalunos = new JLayeredPane();
		tabbedPane.addTab("Gerenciar Alunos", null, abaalunos, null);
		JButton btnAdicionarAluno = new JButton("Adicionar Aluno");
		btnAdicionarAluno.setBounds(10, 458, 153, 23);
		abaalunos.add(btnAdicionarAluno);
		//Metodo adicionar
		btnAdicionarAluno.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				btnAdicionarAlunoClick();		
			}
		});
		btnAdicionarAluno.setToolTipText("Adicione um novo aluno");		
		
		JButton btnExcluirAluno = new JButton("Excluir Aluno");
		btnExcluirAluno.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				btnExcluirAlunoClick();
			}
		});
		btnExcluirAluno.setBounds(215, 458, 154, 23);
		abaalunos.add(btnExcluirAluno);
		btnExcluirAluno.setToolTipText("Exclua um aluno cadastrado");
		
		JButton btnAtualizarDados = new JButton("Atualizar Dados");
		btnAtualizarDados.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				btnAtualizarDadosClick();
			}
		});
		btnAtualizarDados.setBounds(428, 458, 144, 23);
		abaalunos.add(btnAtualizarDados);
		btnAtualizarDados.setToolTipText("Atualize os Dados");

		tabela = new TabelaAlunos(TelaPrincipal.db.getAlunos(), colunasAlunos);
		tabela.setRowSelectionAllowed(true);
		rolagem = new JScrollPane(tabela);
		rolagem.setBounds(10, 11, 765, 444);
		abaalunos.add(rolagem);
		
		JButton btnComprarTicket = new JButton("Comprar Ticket");
		btnComprarTicket.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
						comprarTicketsClick();
			}
		});
		btnComprarTicket.setBounds(622, 458, 153, 23);
		abaalunos.add(btnComprarTicket);


		//Aba de funcionarios----------------------------------------------------------------------------
		JLayeredPane abafuncionarios = new JLayeredPane();
		tabbedPane.addTab("Gerenciar Funcionários", null, abafuncionarios, null);
		JButton btnAdicionarFuncionario = new JButton("Adicionar Funcionário");
		btnAdicionarFuncionario.setBounds(10, 458, 160, 23);
		abafuncionarios.add(btnAdicionarFuncionario);
		btnAdicionarFuncionario.addActionListener(new ActionListener() {			
			@Override
			public void actionPerformed(ActionEvent e) {
				btnAdicionarFuncionarioClick();

			}
		});
		btnAdicionarFuncionario.setToolTipText("Adicione um novo funcinário");		
		JButton btnExcluirFuncionario = new JButton("Excluir Funcionário");
		btnExcluirFuncionario.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				btnExcluirFuncionarioClick();
			}
		});
		btnExcluirFuncionario.setBounds(216, 458, 154, 23);
		abafuncionarios.add(btnExcluirFuncionario);
		btnExcluirFuncionario.setToolTipText("Exclua um funcionário cadastrado");		
		JButton btnAtualizarDados1 = new JButton("Atualizar Dados");
		btnAtualizarDados1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				btnAtualizarDadosFuncionarioClick();
			}
		});
		btnAtualizarDados1.setBounds(416, 458, 160, 23);
		abafuncionarios.add(btnAtualizarDados1);
		btnAtualizarDados1.setToolTipText("Atualize os Dados");

		tabela1 = new TabelaFunc(TelaPrincipal.db.getFuncionario(), colunasFuncionarios);
		tabela1.setRowSelectionAllowed(true);
		rolagem1 = new JScrollPane(tabela1);
		rolagem1.setBounds(10, 11, 765, 444);
		abafuncionarios.add(rolagem1);
		
		JButton btnComprarTicket_1 = new JButton("Comprar Ticket");
		
		
		btnComprarTicket_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
						comprarTickets_1Click();
			}
		});
		
		btnComprarTicket_1.setBounds(615, 458, 160, 23);
		abafuncionarios.add(btnComprarTicket_1);

		//Aba de cursos----------------------------------------------------------------------------------
		JLayeredPane abacurso = new JLayeredPane();
		tabbedPane.addTab("Cursos", null, abacurso, null);
		JButton btnAdicionarCurso = new JButton("Adicionar Curso");
		btnAdicionarCurso.setBounds(180, 458, 170, 23);
		abacurso.add(btnAdicionarCurso);
		btnAdicionarCurso.addActionListener(new ActionListener() {			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				btnAdicionarCursoClick();

			}
		});
		btnAdicionarCurso.setToolTipText("Adicione um novo curso");		
		JButton btnExcluirCurso = new JButton("Excluir Curso");
		btnExcluirCurso.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				btnExcluirCursoClick();
			}
		});
		btnExcluirCurso.setBounds(400, 458, 154, 23);
		abacurso.add(btnExcluirCurso);
		btnExcluirCurso.setToolTipText("Exclua um curso");		

		tabela2 = new TabelaCursos(TelaPrincipal.db.getCurso(), colunasCurso);
		tabela2.setRowSelectionAllowed(true);
		rolagem2 = new JScrollPane(tabela2);
		rolagem2.setBounds(10, 11, 765, 444);
		abacurso.add(rolagem2);

		//Aba de Departamentos---------------------------------------------------------------------------
		JLayeredPane abadept = new JLayeredPane();
		tabbedPane.addTab("Departamentos", null, abadept, null);
		JButton btnAdicionarDept= new JButton("Adicionar Departamento");
		btnAdicionarDept.setBounds(170, 458, 180, 23);
		abadept.add(btnAdicionarDept);
		btnAdicionarDept.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				btnAdicionarDeptsClick();

			}
		});

		btnAdicionarDept.setToolTipText("Adicione um novo departamento");		
		JButton btnExcluirDept = new JButton("Excluir Departamento");
		btnExcluirDept.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				btnExcluirDepartamentoClick();
			}
		});
		btnExcluirDept.setBounds(400, 458, 165, 23);
		abadept.add(btnExcluirDept);
		btnExcluirDept.setToolTipText("Exclua um Departamento");		

		tabela3 = new TabelaDept(TelaPrincipal.db.getDept(), colunasDept);
		tabela3.setRowSelectionAllowed(true);
		rolagem3 = new JScrollPane(tabela3);
		rolagem3.setBounds(10, 11, 765, 444);
		abadept.add(rolagem3);


		//Aba de Refeiçao--------------------------------------------------------------------------------
		abarefeicao = new JLayeredPane();
		tabbedPane.addTab("Refeição", null, abarefeicao, null);

		JTabbedPane tabbedPane_2 = new JTabbedPane(JTabbedPane.LEFT);
		tabbedPane_2.setBounds(36, 28, 713, 306);
		abarefeicao.add(tabbedPane_2);

		Desjejum = new JLayeredPane();
		Desjejum.setForeground(Color.WHITE);
		tabbedPane_2.addTab("Manhã", null, Desjejum, null);

		JLabel lblDesjejum = new JLabel("Desjejum");
		lblDesjejum.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lblDesjejum.setBounds(10, -3, 114, 50);
		Desjejum.add(lblDesjejum);

		JLabel lblDescrio = new JLabel("Descrição");
		lblDescrio.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblDescrio.setBounds(50, 42, 200, 50);
		Desjejum.add(lblDescrio);

		JButton btnNewButton = new JButton("Alterar Desjejum");
		btnNewButton.setBounds(495, 98, 150, 85);
		Desjejum.add(btnNewButton);
		
		desjejumLista = new JList();
		desjejumScroll = new JScrollPane(desjejumLista);
		TelaPrincipal.Desjejum.add(desjejumScroll);
		desjejumScroll.setBounds(50, 75, 345, 170);
		
		
		btnNewButton.addActionListener(new ActionListener() {			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				btnButtonClick();

			}
		});

		Almoco = new JLayeredPane();
		Almoco.setForeground(Color.WHITE);
		tabbedPane_2.addTab("Tarde", null, Almoco, null);

		JLabel lblAlmoco = new JLabel("Almoço");
		lblAlmoco.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lblAlmoco.setBounds(10, -3, 114, 50);
		Almoco.add(lblAlmoco);

		JLabel lblDescriAl = new JLabel("Descrição");
		lblDescriAl.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblDescriAl.setBounds(50, 42, 200, 50);
		Almoco.add(lblDescriAl);
		
		JButton btnNewButton1 = new JButton("Alterar Almoço");
		btnNewButton1.setBounds(495, 98, 150, 85);
		Almoco.add(btnNewButton1);
		
		JComboBox comboBox_2 = new JComboBox();
		comboBox_2.setModel(new DefaultComboBoxModel(new String[] {"Carne de Soja", "Omelete de Legumes", "Quiche de Queijo", "Tofu"}));
		comboBox_2.setBounds(195, 270, 200, 20);
		Almoco.add(comboBox_2);
		
		JLabel label = new JLabel("Op\u00E7\u00E3o Vegetariana:");
		label.setFont(new Font("Tahoma", Font.PLAIN, 14));
		label.setBounds(50, 270, 128, 20);
		Almoco.add(label);
		
		almocoLista = new JList();    
		almocoScroll = new JScrollPane(almocoLista);
		TelaPrincipal.Almoco.add(almocoScroll);
		almocoScroll.setBounds(50, 75, 345, 170);
		
		btnNewButton1.addActionListener(new ActionListener() {			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				btnButtonClick1();

			}
		});

		Jantar = new JLayeredPane();
		Jantar.setForeground(Color.WHITE);
		tabbedPane_2.addTab("Noite", null, Jantar, null);

		JLabel lbljantar = new JLabel("Jantar");
		lbljantar.setFont(new Font("Tahoma", Font.PLAIN, 18));
		lbljantar.setBounds(10, -3, 114, 50);
		Jantar.add(lbljantar);

		JLabel lblDescrija = new JLabel("Descrição");
		lblDescrija.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblDescrija.setBounds(50, 42, 200, 50);
		Jantar.add(lblDescrija);

		JButton btnNewButton2 = new JButton("Alterar Jantar");
		btnNewButton2.setBounds(495, 98, 150, 85);
		Jantar.add(btnNewButton2);
		
		JComboBox comboBox_3 = new JComboBox();
		comboBox_3.setModel(new DefaultComboBoxModel(new String[] {"Carne de Soja", "Omelete de Legumes", "Quiche de Queijo", "Tofu"}));
		comboBox_3.setBounds(195, 270, 200, 20);
		Jantar.add(comboBox_3);
		
		JLabel label_1 = new JLabel("Op\u00E7\u00E3o Vegetariana:");
		label_1.setFont(new Font("Tahoma", Font.PLAIN, 14));
		label_1.setBounds(50, 270, 128, 20);
		Jantar.add(label_1);
		
		jantarLista = new JList();    
		jantarScroll = new JScrollPane(jantarLista);
		TelaPrincipal.Jantar.add(jantarScroll);
		jantarScroll.setBounds(50, 75, 345, 170);
		
		btnNewButton2.addActionListener(new ActionListener() {			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				btnButtonClick2();

			}
		});
		//Menu Superior----------------------------------------------------------------------------------
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);

		JMenu mnArquivo = new JMenu("Arquivo");
		menuBar.add(mnArquivo);

		JMenuItem mntmSave = new JMenuItem("Salvar Alterações");
		mnArquivo.add(mntmSave);
		mntmSave.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent arg0) {
			salvarAlteracoesClick();
			}
		});
		
		JMenuItem mntmdesSave = new JMenuItem("Abrir Último");
		mnArquivo.add(mntmdesSave);
		mntmdesSave.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				SerializaDataBase.DesserializarDataBase("MeuSql");
				 tabela.preencheVazio();
				 tabela1.preencheVazio();
				 tabela2.preencheVazio();
				 tabela3.preencheVazio();
				 tabela.preenche();
				 tabela1.preenche();
				 tabela2.preenche();
				 tabela3.preenche();
				 
				
			}
		});
	
		JMenu mnConfiguracoes = new JMenu("Configurações");
		menuBar.add(mnConfiguracoes);
		
		JMenu mnAjuda = new JMenu("Ajuda");
		menuBar.add(mnAjuda);
		
		JMenuItem mntmLogin = new JMenuItem("Trocar Login/Senha");
		mntmLogin.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				trocarLoginClick();
			}
		});
		mnConfiguracoes.add(mntmLogin);

		JMenuItem mntmSobre = new JMenuItem("Sobre");
		mnAjuda.add(mntmSobre);
		//Metodo Sobre
		mntmSobre.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				mntmSobreClick();		
			}
		});
		frame.setResizable(false);
		
		//DataBase.instanciarPadrao();
	}

	//metodos buttons click-----------------------------------------------------------------------------
	private void trocarLoginClick(){
		TrocarLogin log = new TrocarLogin();
		log.frame.setVisible(true);
	}
	
	private void salvarAlteracoesClick(){
		SerializaDataBase.SerealizarDataBase("MeuSql", db);
	}
	
	private void btnButtonClick(){
		Desjejum dualList1 = new Desjejum();
		dualList1.setVisible();
	}	
	private void btnButtonClick1(){
		Almoco dualList2 = new Almoco();
		dualList2.setVisible();
	}
	private void btnButtonClick2(){
		Jantar dualList3 = new Jantar();
		dualList3.setVisible();
	}
	private void mntmSobreClick(){
		Sobre sobre = new Sobre();
		sobre.frame.setVisible(true);
	}
	private void btnAdicionarDeptsClick(){
		AdicionarDepts adddep = new AdicionarDepts();
		adddep.frame.setVisible(true);
	}
	private void btnAdicionarCursoClick(){
		AdicionarCurso addcurso = new AdicionarCurso();
		addcurso.frame.setVisible(true);

	}
	private void btnAdicionarFuncionarioClick(){
		AdicionarFuncionario addfun = new AdicionarFuncionario();
		addfun.frame.setVisible(true);
	}
	private void btnAdicionarAlunoClick(){
		AdicionarAluno addaluno = new AdicionarAluno();
		addaluno.frame.setVisible(true);
	}
	private void btnExcluirAlunoClick(){
		
		TelaPrincipal.db.getAlunos().remove(tabela.getSelectedRow());
		System.out.println(TelaPrincipal.db.getAlunos().size());	
		tabela.preencheVazio();
		tabela.preenche();
	}
	
	private void btnAtualizarDadosClick(){
		AtualizarDados atDados = new AtualizarDados();
		atDados.frame.setVisible(true);
		
//		DataBase.getAlunos().get(tabela.getSelectedRow());
		
	}
	
	private void btnAtualizarDadosFuncionarioClick(){
		AtualizarDadosFuncionario atDadosFuncionario = new AtualizarDadosFuncionario();
		atDadosFuncionario.frame.setVisible(true);
	}
	
	private void comprarTicketsClick(){
		
		VendaTicketAluno venda = new VendaTicketAluno();
		venda.frame.setVisible(true);
	}
	
	
	private void comprarTickets_1Click(){
		VendaTicketFunc venda = new VendaTicketFunc();
		venda.frame.setVisible(true);
	}
	
	private void btnExcluirFuncionarioClick(){
		TelaPrincipal.db.getFuncionario().remove(tabela1.getSelectedRow());
		System.out.println(TelaPrincipal.db.getFuncionario().size());	
		tabela1.preencheVazio();
		tabela1.preenche();
	}
	
	
	private void btnExcluirCursoClick(){
		TelaPrincipal.db.getCurso().remove(tabela2.getSelectedRow());
		System.out.println(TelaPrincipal.db.getCurso().size());	
		tabela2.preencheVazio();
		tabela2.preenche();
	}
	
	private void btnExcluirDepartamentoClick(){
		TelaPrincipal.db.getDept().remove(tabela3.getSelectedRow());
		System.out.println(TelaPrincipal.db.getDept().size());	
		tabela3.preencheVazio();
		tabela3.preenche();
	}
}
