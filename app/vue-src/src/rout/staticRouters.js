const staticRouters = [
  { path: '/',
    name: 'index',
    component: () => import('../components/AppIndex.vue') 
	},
];
export default staticRouters;