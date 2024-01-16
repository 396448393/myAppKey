<template>
	<div>
		<el-table :data="tableData" style="width: 100%">
			<el-table-column prop="user" label="用户" width="180">
			</el-table-column>
		</el-table>
	</div>
</template>

<script>
	import axios from 'axios'
	export default {
		name: "Manager",
		props: {
		    userId: String,
      tableData: Array,
		  },
		data() {
			return {
			}
		},
		methods: {

		}
	}
</script>

<style>
</style>
