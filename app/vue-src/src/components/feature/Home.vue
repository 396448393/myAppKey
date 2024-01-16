<template>
	<div>
		<el-form ref="homeForm" :model="homeForm" label-width="120px">
			<el-form-item label="服务器链接状态">
				<el-switch v-model="homeForm.connectionStatus" active-color="#13ce66" inactive-color="#ff4949" disabled="disabled">
				</el-switch>
        <el-button @click="testConnection">测试连接</el-button>
			</el-form-item>
			<el-form-item label="锁状态" v-if="homeForm.connectionStatus">
				<el-switch v-model="homeForm.lockState" active-color="#13ce66" inactive-color="#ff4949" @change="onChange">
				</el-switch>
			</el-form-item>
		</el-form>
	</div>
</template>

<script>
	import axios from 'axios'
	export default {
		name: "Home",
		props: {
			userId: String,
      homeForm: Object
		},
		data() {
			return {
			}
		},
		methods: {
      onChange(val) {
        this.$emit('changeSwitch',val)
      },
      testConnection() {
        this.$emit('testButton')
      }


		}
	}
</script>

<style>
</style>
